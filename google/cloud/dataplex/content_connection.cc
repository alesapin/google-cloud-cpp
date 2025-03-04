// Copyright 2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Generated by the Codegen C++ plugin.
// If you make any local changes, they will be lost.
// source: google/cloud/dataplex/v1/content.proto

#include "google/cloud/dataplex/content_connection.h"
#include "google/cloud/dataplex/content_options.h"
#include "google/cloud/dataplex/internal/content_connection_impl.h"
#include "google/cloud/dataplex/internal/content_option_defaults.h"
#include "google/cloud/dataplex/internal/content_stub_factory.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/common_options.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/pagination_range.h"
#include <memory>

namespace google {
namespace cloud {
namespace dataplex {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

ContentServiceConnection::~ContentServiceConnection() = default;

StatusOr<google::cloud::dataplex::v1::Content>
ContentServiceConnection::CreateContent(
    google::cloud::dataplex::v1::CreateContentRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::cloud::dataplex::v1::Content>
ContentServiceConnection::UpdateContent(
    google::cloud::dataplex::v1::UpdateContentRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

Status ContentServiceConnection::DeleteContent(
    google::cloud::dataplex::v1::DeleteContentRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::cloud::dataplex::v1::Content>
ContentServiceConnection::GetContent(
    google::cloud::dataplex::v1::GetContentRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StreamRange<google::cloud::dataplex::v1::Content>
ContentServiceConnection::ListContent(
    google::cloud::dataplex::v1::
        ListContentRequest) {  // NOLINT(performance-unnecessary-value-param)
  return google::cloud::internal::MakeUnimplementedPaginationRange<
      StreamRange<google::cloud::dataplex::v1::Content>>();
}

std::shared_ptr<ContentServiceConnection> MakeContentServiceConnection(
    Options options) {
  internal::CheckExpectedOptions<CommonOptionList, GrpcOptionList,
                                 ContentServicePolicyOptionList>(options,
                                                                 __func__);
  options = dataplex_internal::ContentServiceDefaultOptions(std::move(options));
  auto background = internal::MakeBackgroundThreadsFactory(options)();
  auto stub = dataplex_internal::CreateDefaultContentServiceStub(
      background->cq(), options);
  return std::make_shared<dataplex_internal::ContentServiceConnectionImpl>(
      std::move(background), std::move(stub), std::move(options));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace dataplex
}  // namespace cloud
}  // namespace google

namespace google {
namespace cloud {
namespace dataplex_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::shared_ptr<dataplex::ContentServiceConnection>
MakeContentServiceConnection(std::shared_ptr<ContentServiceStub> stub,
                             Options options) {
  options = ContentServiceDefaultOptions(std::move(options));
  auto background = internal::MakeBackgroundThreadsFactory(options)();
  return std::make_shared<dataplex_internal::ContentServiceConnectionImpl>(
      std::move(background), std::move(stub), std::move(options));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace dataplex_internal
}  // namespace cloud
}  // namespace google
