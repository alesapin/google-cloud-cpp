// Copyright 2019 Google LLC
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

#include "google/cloud/storage/internal/grpc_object_read_source.h"
#include "google/cloud/storage/hashing_options.h"
#include "google/cloud/storage/internal/grpc_object_metadata_parser.h"
#include "google/cloud/testing_util/status_matchers.h"
#include "absl/memory/memory.h"
#include <google/protobuf/text_format.h>
#include <google/protobuf/util/message_differencer.h>
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace storage {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace internal {
namespace {

using ::google::cloud::internal::StreamingRpcMetadata;
using ::google::cloud::testing_util::StatusIs;
using ::testing::ByMove;
using ::testing::HasSubstr;
using ::testing::Return;

namespace storage_proto = ::google::storage::v2;

class MockStream : public google::cloud::internal::AsyncStreamingReadRpc<
                       storage_proto::ReadObjectResponse> {
 public:
  MOCK_METHOD(future<bool>, Start, (), (override));
  MOCK_METHOD(future<absl::optional<storage_proto::ReadObjectResponse>>, Read,
              (), (override));
  MOCK_METHOD(future<Status>, Finish, (), (override));
  MOCK_METHOD(void, Cancel, (), (override));
  MOCK_METHOD(StreamingRpcMetadata, GetRequestMetadata, (), (const, override));
};

future<absl::optional<storage_proto::ReadObjectResponse>> MakeClosingRead() {
  return make_ready_future(absl::optional<storage_proto::ReadObjectResponse>());
}

TEST(GrpcObjectReadSource, Simple) {
  auto mock = absl::make_unique<MockStream>();
  ::testing::InSequence sequence;
  EXPECT_CALL(*mock, Read)
      .WillOnce([]() {
        storage_proto::ReadObjectResponse response;
        response.mutable_checksummed_data()->set_content("0123456789");
        return make_ready_future(absl::make_optional(response));
      })
      .WillOnce([]() {
        storage_proto::ReadObjectResponse response;
        response.mutable_checksummed_data()->set_content(
            " The quick brown fox jumps over the lazy dog");
        return make_ready_future(absl::make_optional(response));
      })
      .WillOnce(Return(ByMove(MakeClosingRead())));
  EXPECT_CALL(*mock, Finish)
      .WillOnce(Return(ByMove(make_ready_future(Status{}))));
  EXPECT_CALL(*mock, GetRequestMetadata)
      .WillOnce(Return(StreamingRpcMetadata{}));
  GrpcObjectReadSource tested(std::move(mock), std::chrono::seconds(5));
  std::string expected =
      "0123456789 The quick brown fox jumps over the lazy dog";
  std::vector<char> buffer(1024);
  auto response = tested.Read(buffer.data(), buffer.size());
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(expected.size(), response->bytes_received);
  EXPECT_EQ(100, response->response.status_code);
  std::string actual(buffer.data(), expected.size());
  EXPECT_EQ(expected, actual);

  auto status = tested.Close();
  EXPECT_STATUS_OK(status);
  EXPECT_EQ(200, status->status_code);
}

TEST(GrpcObjectReadSource, EmptyWithError) {
  auto mock = absl::make_unique<MockStream>();

  ::testing::InSequence sequence;
  EXPECT_CALL(*mock, Read).WillOnce(Return(ByMove(MakeClosingRead())));
  EXPECT_CALL(*mock, Finish)
      .WillOnce(Return(ByMove(
          make_ready_future(Status(StatusCode::kPermissionDenied, "uh-oh")))));
  EXPECT_CALL(*mock, GetRequestMetadata)
      .WillOnce(Return(StreamingRpcMetadata{}));
  GrpcObjectReadSource tested(std::move(mock), std::chrono::seconds(5));
  std::vector<char> buffer(1024);
  EXPECT_THAT(tested.Read(buffer.data(), buffer.size()),
              StatusIs(StatusCode::kPermissionDenied, HasSubstr("uh-oh")));

  EXPECT_THAT(tested.Close(),
              StatusIs(StatusCode::kPermissionDenied, HasSubstr("uh-oh")));
}

TEST(GrpcObjectReadSource, DataWithError) {
  auto mock = absl::make_unique<MockStream>();

  ::testing::InSequence sequence;
  EXPECT_CALL(*mock, Read)
      .WillOnce([]() {
        storage_proto::ReadObjectResponse response;
        response.mutable_checksummed_data()->set_content("0123456789");
        return make_ready_future(absl::make_optional(response));
      })
      .WillOnce(Return(ByMove(MakeClosingRead())));
  EXPECT_CALL(*mock, Finish)
      .WillOnce(Return(ByMove(
          make_ready_future(Status(StatusCode::kPermissionDenied, "uh-oh")))));
  EXPECT_CALL(*mock, GetRequestMetadata)
      .WillOnce(Return(StreamingRpcMetadata{}));
  GrpcObjectReadSource tested(std::move(mock), std::chrono::seconds(5));
  std::string expected = "0123456789";
  std::vector<char> buffer(1024);
  auto response = tested.Read(buffer.data(), buffer.size());
  EXPECT_FALSE(tested.IsOpen());
  EXPECT_THAT(response,
              StatusIs(StatusCode::kPermissionDenied, HasSubstr("uh-oh")));

  EXPECT_THAT(tested.Close(),
              StatusIs(StatusCode::kPermissionDenied, HasSubstr("uh-oh")));
}

TEST(GrpcObjectReadSource, UseSpillBuffer) {
  auto mock = absl::make_unique<MockStream>();
  auto const trailer_size = 1024;
  std::string const expected_1 = "0123456789";
  std::string const expected_2(trailer_size, 'A');
  ASSERT_LT(expected_1.size(), expected_2.size());
  std::string const contents = expected_1 + expected_2;

  ::testing::InSequence sequence;
  EXPECT_CALL(*mock, Read)
      .WillOnce([&contents]() {
        storage_proto::ReadObjectResponse response;
        response.mutable_checksummed_data()->set_content(contents);
        return make_ready_future(absl::make_optional(response));
      })
      .WillOnce(Return(ByMove(MakeClosingRead())));
  EXPECT_CALL(*mock, Finish)
      .WillOnce(Return(ByMove(make_ready_future(Status{}))));
  EXPECT_CALL(*mock, GetRequestMetadata)
      .WillOnce(Return(StreamingRpcMetadata{}));
  GrpcObjectReadSource tested(std::move(mock), std::chrono::seconds(5));
  std::vector<char> buffer(trailer_size);
  auto response = tested.Read(buffer.data(), expected_1.size());
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(expected_1.size(), response->bytes_received);
  std::string actual(buffer.data(), response->bytes_received);
  EXPECT_EQ(expected_1, actual);

  response = tested.Read(buffer.data(), buffer.size());
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(expected_2.size(), response->bytes_received);
  actual = std::string(buffer.data(), response->bytes_received);
  EXPECT_EQ(expected_2, actual);

  response = tested.Read(buffer.data(), buffer.size());
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(0, response->bytes_received);

  auto status = tested.Close();
  EXPECT_STATUS_OK(status);
}

TEST(GrpcObjectReadSource, UseSpillBufferMany) {
  auto mock = absl::make_unique<MockStream>();
  std::string const contents = "0123456789";

  ::testing::InSequence sequence;
  EXPECT_CALL(*mock, Read)
      .WillOnce([&contents]() {
        storage_proto::ReadObjectResponse response;
        response.mutable_checksummed_data()->set_content(contents);
        return make_ready_future(absl::make_optional(response));
      })
      .WillOnce(Return(ByMove(MakeClosingRead())));
  EXPECT_CALL(*mock, Finish)
      .WillOnce(Return(ByMove(make_ready_future(Status{}))));
  EXPECT_CALL(*mock, GetRequestMetadata)
      .WillOnce(Return(StreamingRpcMetadata{}));
  GrpcObjectReadSource tested(std::move(mock), std::chrono::seconds(5));
  std::vector<char> buffer(1024);
  auto response = tested.Read(buffer.data(), 3);
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(3, response->bytes_received);
  auto actual = std::string(buffer.data(), response->bytes_received);
  EXPECT_EQ("012", actual);

  response = tested.Read(buffer.data(), 4);
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(4, response->bytes_received);
  actual = std::string(buffer.data(), response->bytes_received);
  EXPECT_EQ("3456", actual);

  response = tested.Read(buffer.data(), buffer.size());
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(3, response->bytes_received);
  actual = std::string(buffer.data(), response->bytes_received);
  EXPECT_EQ("789", actual);

  response = tested.Read(buffer.data(), buffer.size());
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(0, response->bytes_received);

  auto status = tested.Close();
  EXPECT_STATUS_OK(status);
}

TEST(GrpcObjectReadSource, CaptureChecksums) {
  auto mock = absl::make_unique<MockStream>();
  std::string const expected_payload =
      "The quick brown fox jumps over the lazy dog";
  auto const expected_md5 = ComputeMD5Hash(expected_payload);
  auto const expected_crc32c = ComputeCrc32cChecksum(expected_payload);

  ::testing::InSequence sequence;
  EXPECT_CALL(*mock, Read)
      .WillOnce([&]() {
        storage_proto::ReadObjectResponse response;
        response.mutable_checksummed_data()->set_content("The quick brown");
        response.mutable_object_checksums()->set_md5_hash(
            GrpcObjectMetadataParser::MD5ToProto(expected_md5).value());
        response.mutable_object_checksums()->set_crc32c(
            GrpcObjectMetadataParser::Crc32cToProto(expected_crc32c).value());
        return make_ready_future(absl::make_optional(response));
      })
      .WillOnce([&] {
        storage_proto::ReadObjectResponse response;
        response.mutable_checksummed_data()->set_content(
            " fox jumps over the lazy dog");
        // The headers may be included more than once in the stream,
        // `GrpcObjectReadSource` should return them only once.
        response.mutable_object_checksums()->set_md5_hash(
            GrpcObjectMetadataParser::MD5ToProto(expected_md5).value());
        response.mutable_object_checksums()->set_crc32c(
            GrpcObjectMetadataParser::Crc32cToProto(expected_crc32c).value());
        return make_ready_future(absl::make_optional(response));
      })
      .WillOnce(Return(ByMove(MakeClosingRead())));
  EXPECT_CALL(*mock, Finish)
      .WillOnce(Return(ByMove(make_ready_future(Status{}))));
  EXPECT_CALL(*mock, GetRequestMetadata)
      .WillOnce(Return(StreamingRpcMetadata{}));
  GrpcObjectReadSource tested(std::move(mock), std::chrono::seconds(5));
  std::vector<char> buffer(1024);
  auto response = tested.Read(buffer.data(), buffer.size());
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(expected_payload.size(), response->bytes_received);
  EXPECT_EQ(100, response->response.status_code);
  auto const actual = std::string(buffer.data(), response->bytes_received);
  EXPECT_EQ(expected_payload, actual);
  EXPECT_EQ(response->hashes.crc32c, expected_crc32c);
  EXPECT_EQ(response->hashes.md5, expected_md5);

  auto status = tested.Close();
  EXPECT_STATUS_OK(status);
  EXPECT_EQ(200, status->status_code);
}

TEST(GrpcObjectReadSource, CaptureGeneration) {
  auto mock = absl::make_unique<MockStream>();
  std::string const expected_payload =
      "The quick brown fox jumps over the lazy dog";
  EXPECT_CALL(*mock, Read)
      .WillOnce([&] {
        // Generate a response that includes the generation, but not enough data
        // to return immediately.
        storage_proto::ReadObjectResponse response;
        response.mutable_metadata()->set_generation(1234);
        response.mutable_checksummed_data()->set_content("The quick brown");
        return make_ready_future(absl::make_optional(response));
      })
      .WillOnce([&] {
        // The last response, without metadata or generation.
        storage_proto::ReadObjectResponse response;
        response.mutable_checksummed_data()->set_content(
            " fox jumps over the lazy dog");
        return make_ready_future(absl::make_optional(response));
      })
      .WillOnce(Return(ByMove(MakeClosingRead())));
  EXPECT_CALL(*mock, Finish)
      .WillOnce(Return(ByMove(make_ready_future(Status{}))));
  EXPECT_CALL(*mock, GetRequestMetadata)
      .WillOnce(Return(StreamingRpcMetadata{}));

  GrpcObjectReadSource tested(std::move(mock), std::chrono::seconds(5));
  std::vector<char> buffer(1024);
  auto response = tested.Read(buffer.data(), buffer.size());
  ASSERT_STATUS_OK(response);
  // The generation is captured on any message that contains it, and saved until
  // it can be returned.
  EXPECT_EQ(1234, response->generation.value_or(0));
}

TEST(GrpcObjectReadSource, HandleEmptyResponses) {
  auto mock = absl::make_unique<MockStream>();
  auto make_empty_response = [] {
    return make_ready_future(
        absl::make_optional(storage_proto::ReadObjectResponse{}));
  };
  EXPECT_CALL(*mock, Read)
      .WillOnce(make_empty_response)
      .WillOnce([]() {
        storage_proto::ReadObjectResponse response;
        response.mutable_checksummed_data()->set_content("The quick brown ");
        return make_ready_future(absl::make_optional(response));
      })
      .WillOnce(make_empty_response)
      .WillOnce([]() {
        storage_proto::ReadObjectResponse response;
        response.mutable_checksummed_data()->set_content("fox jumps over ");
        return make_ready_future(absl::make_optional(response));
      })
      .WillOnce(make_empty_response)
      .WillOnce([]() {
        storage_proto::ReadObjectResponse response;
        response.mutable_checksummed_data()->set_content("the lazy dog");
        return make_ready_future(absl::make_optional(response));
      })
      .WillOnce(Return(ByMove(MakeClosingRead())));
  EXPECT_CALL(*mock, Finish)
      .WillOnce(Return(ByMove(make_ready_future(Status{}))));
  EXPECT_CALL(*mock, GetRequestMetadata)
      .WillOnce(Return(StreamingRpcMetadata{}));
  GrpcObjectReadSource tested(std::move(mock), std::chrono::seconds(5));
  std::string const expected = "The quick brown fox jumps over the lazy dog";
  std::vector<char> buffer(1024);
  auto response = tested.Read(buffer.data(), buffer.size());
  EXPECT_STATUS_OK(response);
  EXPECT_EQ(expected.size(), response->bytes_received);
  EXPECT_EQ(100, response->response.status_code);
  std::string actual(buffer.data(), expected.size());
  EXPECT_EQ(expected, actual);

  auto status = tested.Close();
  EXPECT_STATUS_OK(status);
  EXPECT_EQ(200, status->status_code);
}

TEST(GrpcObjectReadSource, HandleExtraRead) {
  auto mock = absl::make_unique<MockStream>();
  EXPECT_CALL(*mock, Read)
      .WillOnce([]() {
        storage_proto::ReadObjectResponse response;
        response.mutable_checksummed_data()->set_content(
            "The quick brown fox jumps over the lazy dog");
        return make_ready_future(absl::make_optional(response));
      })
      .WillOnce(Return(ByMove(MakeClosingRead())));
  EXPECT_CALL(*mock, Finish)
      .WillOnce(Return(ByMove(make_ready_future(Status{}))));
  EXPECT_CALL(*mock, GetRequestMetadata)
      .WillOnce(Return(StreamingRpcMetadata{}));
  GrpcObjectReadSource tested(std::move(mock), std::chrono::seconds(5));
  std::string const expected = "The quick brown fox jumps over the lazy dog";
  std::vector<char> buffer(1024);
  auto response = tested.Read(buffer.data(), buffer.size());
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(expected.size(), response->bytes_received);
  EXPECT_EQ(100, response->response.status_code);
  std::string actual(buffer.data(), expected.size());
  EXPECT_EQ(expected, actual);

  response = tested.Read(buffer.data(), buffer.size());
  ASSERT_STATUS_OK(response);
  EXPECT_EQ(0, response->bytes_received);
  EXPECT_EQ(100, response->response.status_code);

  auto status = tested.Close();
  EXPECT_STATUS_OK(status);
  EXPECT_EQ(200, status->status_code);
}

TEST(GrpcObjectReadSource, StallTimeout) {
  auto mock = absl::make_unique<MockStream>();

  promise<void> hold_response;

  ::testing::InSequence sequence;
  EXPECT_CALL(*mock, Read).WillOnce([&] {
    return hold_response.get_future().then([](future<void>) {
      return absl::optional<storage_proto::ReadObjectResponse>();
    });
  });
  EXPECT_CALL(*mock, Cancel).WillOnce([&] { hold_response.set_value(); });
  EXPECT_CALL(*mock, Finish)
      .WillOnce(Return(ByMove(make_ready_future(Status{}))));

  GrpcObjectReadSource tested(std::move(mock), std::chrono::milliseconds(3));
  std::vector<char> buffer(1024);
  auto response = tested.Read(buffer.data(), buffer.size());
  EXPECT_THAT(response, StatusIs(StatusCode::kDeadlineExceeded));
}

}  // namespace
}  // namespace internal
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace storage
}  // namespace cloud
}  // namespace google
