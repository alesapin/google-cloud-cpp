// Copyright 2018 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "google/cloud/storage/internal/curl_download_request.h"
#include "google/cloud/storage/internal/binary_data_as_debug_string.h"
#include "google/cloud/storage/internal/curl_wrappers.h"
#include "google/cloud/internal/throw_delegate.h"
#include "google/cloud/log.h"
#include <curl/multi.h>
#include <algorithm>
#include <cstring>
#include <thread>

namespace google {
namespace cloud {
namespace storage {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace internal {

std::string ExtractHashValue(std::string const& hash_header,
                             std::string const& hash_key) {
  auto const pos = hash_header.find(hash_key);
  if (pos == std::string::npos) return {};
  auto const start = pos + hash_key.size();
  auto const end = hash_header.find(',', start);
  if (end == std::string::npos) {
    return hash_header.substr(start);
  }
  return hash_header.substr(start, end - start);
}

ReadSourceResult MakeReadResult(std::size_t bytes_received,
                                HttpResponse response) {
  auto r = ReadSourceResult{bytes_received, std::move(response)};
  auto const end = r.response.headers.end();
  auto f = r.response.headers.find("x-goog-generation");
  if (f != end && !r.generation) r.generation = std::stoll(f->second);
  f = r.response.headers.find("x-goog-metageneration");
  if (f != end && !r.metageneration) r.metageneration = std::stoll(f->second);
  f = r.response.headers.find("x-goog-storage-class");
  if (f != end && !r.storage_class) r.storage_class = f->second;
  f = r.response.headers.find("x-goog-stored-content-length");
  if (f != end && !r.size) r.size = std::stoull(f->second);
  f = r.response.headers.find("x-guploader-response-body-transformations");
  if (f != end && !r.transformation) r.transformation = f->second;

  // Prefer "Content-Range" over "Content-Length" because the former works for
  // ranged downloads.
  f = r.response.headers.find("content-range");
  if (f != end && !r.size) {
    auto const l = f->second.find_last_of('/');
    if (l != std::string::npos) r.size = std::stoll(f->second.substr(l + 1));
  }
  f = r.response.headers.find("content-length");
  if (f != end && !r.size) r.size = std::stoll(f->second);

  // x-goog-hash is special in that it does appear multiple times in the
  // headers, and we want to accumulate all the values.
  auto const range = r.response.headers.equal_range("x-goog-hash");
  for (auto i = range.first; i != range.second; ++i) {
    HashValues h;
    h.crc32c = ExtractHashValue(i->second, "crc32c=");
    h.md5 = ExtractHashValue(i->second, "md5=");
    r.hashes = Merge(std::move(r.hashes), std::move(h));
  }
  return r;
}

extern "C" std::size_t CurlDownloadRequestWrite(char* ptr, size_t size,
                                                size_t nmemb, void* userdata) {
  auto* request = reinterpret_cast<CurlDownloadRequest*>(userdata);
  return request->WriteCallback(ptr, size, nmemb);
}

extern "C" std::size_t CurlDownloadRequestHeader(char* contents,
                                                 std::size_t size,
                                                 std::size_t nitems,
                                                 void* userdata) {
  auto* request = reinterpret_cast<CurlDownloadRequest*>(userdata);
  return request->HeaderCallback(contents, size, nitems);
}

// Note that TRACE-level messages are disabled by default, even in
// `CMAKE_BUILD_TYPE=Debug` builds. The level of detail created by the
// `TRACE_STATE()` macro is only needed by the library developers when
// troubleshooting this class.
#define TRACE_STATE()                                                       \
  GCP_LOG(TRACE) << __func__ << "(), buffer_size_=" << buffer_size_         \
                 << ", buffer_offset_=" << buffer_offset_                   \
                 << ", spill_.size()=" << spill_.size()                     \
                 << ", spill_offset_=" << spill_offset_                     \
                 << ", closing=" << closing_ << ", closed=" << curl_closed_ \
                 << ", paused=" << paused_ << ", in_multi=" << in_multi_

CurlDownloadRequest::CurlDownloadRequest(CurlHeaders headers, CurlHandle handle,
                                         CurlMulti multi)
    : headers_(std::move(headers)),
      download_stall_timeout_(0),
      handle_(std::move(handle)),
      multi_(std::move(multi)),
      spill_(CURL_MAX_WRITE_SIZE) {}

CurlDownloadRequest::~CurlDownloadRequest() {
  CleanupHandles();
  if (factory_) {
    factory_->CleanupHandle(std::move(handle_));
    factory_->CleanupMultiHandle(std::move(multi_));
  }
}

StatusOr<HttpResponse> CurlDownloadRequest::Close() {
  if (curl_closed_) return HttpResponse{http_code_, {}, received_headers_};
  TRACE_STATE();
  // Set the closing_ flag to trigger a return 0 from the next read
  // callback, see the comments in the header file for more details.
  closing_ = true;
  TRACE_STATE();

  CleanupHandles();

  if (!curl_closed_) {
    // Ignore errors. Except in some really unfortunate cases [*] we are closing
    // the download early. That is done [**] by having the write callback return
    // 0, which always results in libcurl returning `CURLE_WRITE_ERROR`.
    //
    // [*]: the only other case would be the case where a download completes
    //   and the handle is paused because just the right number of bytes
    //   arrived to satisfy the last `Read()` request. In that case ignoring the
    //   errors seems sensible too, the download completed, what is the problem?
    // [**]: this is the recommended practice to shutdown a download early. See
    //   the comments in the header file and elsewhere in this file.
    (void)handle_.EasyPerform();
    curl_closed_ = true;
    TRACE_STATE();
    OnTransferDone();
  }
  return HttpResponse{http_code_, std::string{}, received_headers_};
}

StatusOr<ReadSourceResult> CurlDownloadRequest::Read(char* buf, std::size_t n) {
  buffer_ = buf;
  buffer_offset_ = 0;
  buffer_size_ = n;
  if (n == 0) {
    return Status(StatusCode::kInvalidArgument, "Empty buffer for Read()");
  }
  // Before calling `Wait()` copy any data from the spill buffer into the
  // application buffer. It is possible that `Wait()` will never call
  // `WriteCallback()`, for example, because the Read() or Peek() closed the
  // connection, but if there is any data left in the spill buffer we need
  // to return it.
  DrainSpillBuffer();
  if (curl_closed_) {
    return MakeReadResult(
        buffer_offset_,
        HttpResponse{http_code_, std::string{}, std::move(received_headers_)});
  }

  auto status =
      handle_.SetOption(CURLOPT_WRITEFUNCTION, &CurlDownloadRequestWrite);
  if (!status.ok()) return OnTransferError(std::move(status));
  status = handle_.SetOption(CURLOPT_WRITEDATA, this);
  if (!status.ok()) return OnTransferError(std::move(status));
  status =
      handle_.SetOption(CURLOPT_HEADERFUNCTION, &CurlDownloadRequestHeader);
  if (!status.ok()) return OnTransferError(std::move(status));
  status = handle_.SetOption(CURLOPT_HEADERDATA, this);
  if (!status.ok()) return OnTransferError(std::move(status));

  handle_.FlushDebug(__func__);
  TRACE_STATE();

  if (!curl_closed_ && paused_) {
    paused_ = false;
    status = handle_.EasyPause(CURLPAUSE_RECV_CONT);
    TRACE_STATE() << ", status=" << status;
    if (!status.ok()) return OnTransferError(std::move(status));
  }

  status = Wait([this] {
    return curl_closed_ || paused_ || buffer_offset_ >= buffer_size_;
  });
  TRACE_STATE() << ", status=" << status;
  if (!status.ok()) return OnTransferError(std::move(status));
  auto bytes_read = buffer_offset_;
  buffer_ = nullptr;
  buffer_offset_ = 0;
  buffer_size_ = 0;
  if (curl_closed_) {
    OnTransferDone();
    HttpResponse response{http_code_, std::string{},
                          std::move(received_headers_)};
    status = google::cloud::storage::internal::AsStatus(response);
    TRACE_STATE() << ", status=" << status
                  << ", http code=" << response.status_code;
    if (!status.ok()) return status;
    return MakeReadResult(bytes_read, std::move(response));
  }
  TRACE_STATE() << ", code=100";
  return MakeReadResult(bytes_read, HttpResponse{HttpStatusCode::kContinue,
                                                 {},
                                                 std::move(received_headers_)});
}

void CurlDownloadRequest::CleanupHandles() {
  if (!multi_ != !handle_.handle_) {
    GCP_LOG(FATAL) << "handles are inconsistent, multi_=" << multi_.get()
                   << ", handle_.handle_=" << handle_.handle_.get();
  }
  if (curl_closed_ || !multi_) return;

  if (paused_) {
    paused_ = false;
    (void)handle_.EasyPause(CURLPAUSE_RECV_CONT);
    TRACE_STATE();
  }

  // Now remove the handle from the CURLM* interface and wait for the response.
  if (in_multi_) {
    (void)curl_multi_remove_handle(multi_.get(), handle_.handle_.get());
    in_multi_ = false;
    TRACE_STATE();
  }
}

Status CurlDownloadRequest::SetOptions() {
  auto status = handle_.SetOption(CURLOPT_URL, url_.c_str());
  if (!status.ok()) return OnTransferError(std::move(status));
  status = handle_.SetOption(CURLOPT_HTTPHEADER, headers_.get());
  if (!status.ok()) return OnTransferError(std::move(status));
  status = handle_.SetOption(CURLOPT_USERAGENT, user_agent_.c_str());
  if (!status.ok()) return OnTransferError(std::move(status));
  status = handle_.SetOption(CURLOPT_NOSIGNAL, 1L);
  if (!status.ok()) return OnTransferError(std::move(status));
  status = handle_.SetOption(CURLOPT_NOPROGRESS, 1L);
  if (!status.ok()) return OnTransferError(std::move(status));

  if (!payload_.empty()) {
    status = handle_.SetOption(CURLOPT_POSTFIELDSIZE, payload_.length());
    if (!status.ok()) return OnTransferError(std::move(status));
    status = handle_.SetOption(CURLOPT_POSTFIELDS, payload_.c_str());
    if (!status.ok()) return OnTransferError(std::move(status));
  }
  handle_.EnableLogging(logging_enabled_);
  handle_.SetSocketCallback(socket_options_);
  handle_.SetOptionUnchecked(CURLOPT_HTTP_VERSION,
                             VersionToCurlCode(http_version_));
  if (download_stall_timeout_.count() != 0) {
    // NOLINTNEXTLINE(google-runtime-int) - libcurl *requires* `long`
    auto const timeout = static_cast<long>(download_stall_timeout_.count());
    status = handle_.SetOption(CURLOPT_CONNECTTIMEOUT, timeout);
    if (!status.ok()) return OnTransferError(std::move(status));
    // Timeout if the download receives less than 1 byte/second (i.e.
    // effectively no bytes) for `transfer_stall_timeout_` seconds.
    status = handle_.SetOption(CURLOPT_LOW_SPEED_LIMIT, 1L);
    if (!status.ok()) return OnTransferError(std::move(status));
    status = handle_.SetOption(CURLOPT_LOW_SPEED_TIME, timeout);
    if (!status.ok()) return OnTransferError(std::move(status));
  }
  if (in_multi_) {
    return OnTransferError(Status(StatusCode::kInternal,
                                  "in_multi_ should be false in `SetOptions`"));
  }
  auto error = curl_multi_add_handle(multi_.get(), handle_.handle_.get());
  if (error != CURLM_OK) return OnTransferError(AsStatus(error, __func__));
  in_multi_ = true;
  return Status{};
}

void CurlDownloadRequest::OnTransferDone() {
  // Retrieve the response code for a closed stream. Note the use of
  // `.value()`, this is equivalent to: assert(http_code.ok());
  // The only way the previous call can fail indicates a bug in our code (or
  // corrupted memory), the documentation for CURLINFO_RESPONSE_CODE:
  //   https://curl.haxx.se/libcurl/c/CURLINFO_RESPONSE_CODE.html
  // says:
  //   Returns CURLE_OK if the option is supported, and CURLE_UNKNOWN_OPTION
  //   if not.
  // if the option is not supported then we cannot use HTTP at all in libcurl
  // and the whole library would be unusable.
  http_code_ = handle_.GetResponseCode().value();

  // Capture the peer (the HTTP server), used for troubleshooting.
  received_headers_.emplace(":curl-peer", handle_.GetPeer());
  TRACE_STATE();

  // Release the handles back to the factory as soon as possible, so they can be
  // reused for any other requests.
  if (factory_) {
    factory_->CleanupHandle(std::move(handle_));
    factory_->CleanupMultiHandle(std::move(multi_));
  }
}

Status CurlDownloadRequest::OnTransferError(Status status) {
  // When there is a transfer error the handle is suspect. It could be pointing
  // to an invalid host, a host that is slow and trickling data, or otherwise in
  // a bad state. Release the handle, but do not return it to the pool.
  CleanupHandles();
  auto handle = std::move(handle_);
  if (factory_) {
    // While the handle is suspect, there is probably nothing wrong with the
    // CURLM* handle, that just represents a local resource, such as data
    // structures for `epoll(7)` or `select(2)`
    factory_->CleanupMultiHandle(std::move(multi_));
  }
  return status;
}

void CurlDownloadRequest::DrainSpillBuffer() {
  std::size_t free = buffer_size_ - buffer_offset_;
  auto copy_count = (std::min)(free, spill_offset_);
  std::copy(spill_.data(), spill_.data() + copy_count,
            buffer_ + buffer_offset_);
  buffer_offset_ += copy_count;
  std::memmove(spill_.data(), spill_.data() + copy_count,
               spill_.size() - copy_count);
  spill_offset_ -= copy_count;
}

std::size_t CurlDownloadRequest::WriteCallback(void* ptr, std::size_t size,
                                               std::size_t nmemb) {
  handle_.FlushDebug(__func__);
  TRACE_STATE() << ", n=" << size * nmemb;
  // This transfer is closing, just return zero, that will make libcurl finish
  // any pending work, and will return the handle_ pointer from
  // curl_multi_info_read() in PerformWork(). That is the point where
  // `curl_closed_` is set.
  if (closing_) {
    TRACE_STATE() << " closing";
    return 0;
  }
  if (buffer_offset_ >= buffer_size_) {
    TRACE_STATE() << " *** PAUSING HANDLE ***";
    paused_ = true;
    return CURL_WRITEFUNC_PAUSE;
  }

  // Use the spill buffer first, if there is any...
  DrainSpillBuffer();
  std::size_t free = buffer_size_ - buffer_offset_;
  if (free == 0) {
    TRACE_STATE() << " *** PAUSING HANDLE ***";
    paused_ = true;
    return CURL_WRITEFUNC_PAUSE;
  }
  TRACE_STATE() << ", n=" << size * nmemb << ", free=" << free;

  // Copy the full contents of `ptr` into the application buffer.
  if (size * nmemb < free) {
    std::memcpy(buffer_ + buffer_offset_, ptr, size * nmemb);
    buffer_offset_ += size * nmemb;
    TRACE_STATE() << ", n=" << size * nmemb;
    return size * nmemb;
  }
  // Copy as much as possible from `ptr` into the application buffer.
  std::memcpy(buffer_ + buffer_offset_, ptr, free);
  buffer_offset_ += free;
  spill_offset_ = size * nmemb - free;
  // The rest goes into the spill buffer.
  std::memcpy(spill_.data(), static_cast<char*>(ptr) + free, spill_offset_);
  TRACE_STATE() << ", n=" << size * nmemb << ", free=" << free;
  return size * nmemb;
}

std::size_t CurlDownloadRequest::HeaderCallback(char* contents,
                                                std::size_t size,
                                                std::size_t nitems) {
  return CurlAppendHeaderData(received_headers_, contents, size * nitems);
}

Status CurlDownloadRequest::Wait(absl::FunctionRef<bool()> predicate) {
  int repeats = 0;
  // We can assert that the current thread is the leader, because the
  // predicate is satisfied, and the condition variable exited. Therefore,
  // this thread must run the I/O event loop.
  while (!predicate()) {
    handle_.FlushDebug(__func__);
    TRACE_STATE() << ", repeats=" << repeats;
    auto running_handles = PerformWork();
    if (!running_handles.ok()) return std::move(running_handles).status();
    // Only wait if there are CURL handles with pending work *and* the
    // predicate is not satisfied. Note that if the predicate is ill-defined
    // it might continue to be unsatisfied even though the handles have
    // completed their work.
    if (*running_handles == 0 || predicate()) break;
    auto status = WaitForHandles(repeats);
    if (!status.ok()) return status;
  }
  return Status();
}

StatusOr<int> CurlDownloadRequest::PerformWork() {
  TRACE_STATE();
  if (!in_multi_) {
    return 0;
  }

  // Block while there is work to do, apparently newer versions of libcurl do
  // not need this loop and curl_multi_perform() blocks until there is no more
  // work, but is it pretty harmless to keep here.
  int running_handles = 0;
  CURLMcode result;
  do {
    result = curl_multi_perform(multi_.get(), &running_handles);
  } while (result == CURLM_CALL_MULTI_PERFORM);

  // Throw an exception if the result is unexpected, otherwise return.
  auto status = AsStatus(result, __func__);
  if (!status.ok()) {
    TRACE_STATE() << ", status=" << status;
    return status;
  }
  if (running_handles == 0) {
    // The only way we get here is if the handle "completed", and therefore the
    // transfer either failed or was successful. Pull all the messages out of
    // the info queue until we get the message about our handle.
    int remaining;
    while (auto* msg = curl_multi_info_read(multi_.get(), &remaining)) {
      if (msg->easy_handle != handle_.handle_.get()) {
        // Return an error if this is the wrong handle. This should never
        // happen, if it does we are using the libcurl API incorrectly. But it
        // is better to give a meaningful error message in this case.
        std::ostringstream os;
        os << __func__ << " unknown handle returned by curl_multi_info_read()"
           << ", msg.msg=[" << msg->msg << "]"
           << ", result=[" << msg->data.result
           << "]=" << curl_easy_strerror(msg->data.result);
        return Status(StatusCode::kUnknown, std::move(os).str());
      }
      status = CurlHandle::AsStatus(msg->data.result, __func__);
      TRACE_STATE() << ", status=" << status << ", remaining=" << remaining
                    << ", running_handles=" << running_handles;
      // Whatever the status is, the transfer is done, we need to remove it
      // from the CURLM* interface.
      curl_closed_ = true;
      Status multi_remove_status;
      if (in_multi_) {
        // In the extremely unlikely case that removing the handle from CURLM*
        // was an error, return that as a status.
        multi_remove_status = AsStatus(
            curl_multi_remove_handle(multi_.get(), handle_.handle_.get()),
            __func__);
        in_multi_ = false;
      }

      TRACE_STATE() << ", status=" << status << ", remaining=" << remaining
                    << ", running_handles=" << running_handles
                    << ", multi_remove_status=" << multi_remove_status;

      // Ignore errors when closing the handle. They are expected because
      // libcurl may have received a block of data, but the WriteCallback()
      // (see above) tells libcurl that it cannot receive more data.
      if (closing_) {
        continue;
      }
      if (!status.ok()) {
        return status;
      }
      if (!multi_remove_status.ok()) {
        return multi_remove_status;
      }
    }
  }
  TRACE_STATE() << ", running_handles=" << running_handles;
  return running_handles;
}

Status CurlDownloadRequest::WaitForHandles(int& repeats) {
  int const timeout_ms = 1;
  std::chrono::milliseconds const timeout(timeout_ms);
  int numfds = 0;
  CURLMcode result =
      curl_multi_wait(multi_.get(), nullptr, 0, timeout_ms, &numfds);
  TRACE_STATE() << ", numfds=" << numfds << ", result=" << result
                << ", repeats=" << repeats;
  Status status = AsStatus(result, __func__);
  if (!status.ok()) {
    return status;
  }
  // The documentation for curl_multi_wait() recommends sleeping if it returns
  // numfds == 0 more than once in a row :shrug:
  //    https://curl.haxx.se/libcurl/c/curl_multi_wait.html
  if (numfds == 0) {
    if (++repeats > 1) {
      std::this_thread::sleep_for(timeout);
    }
  } else {
    repeats = 0;
  }
  return status;
}

Status CurlDownloadRequest::AsStatus(CURLMcode result, char const* where) {
  if (result == CURLM_OK) {
    return Status();
  }
  std::ostringstream os;
  os << where << "(): unexpected error code in curl_multi_*, [" << result
     << "]=" << curl_multi_strerror(result);
  return Status(StatusCode::kUnknown, std::move(os).str());
}

}  // namespace internal
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace storage
}  // namespace cloud
}  // namespace google
