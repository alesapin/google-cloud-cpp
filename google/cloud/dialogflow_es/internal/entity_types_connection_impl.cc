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
// source: google/cloud/dialogflow/v2/entity_type.proto

#include "google/cloud/dialogflow_es/internal/entity_types_connection_impl.h"
#include "google/cloud/dialogflow_es/internal/entity_types_option_defaults.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/common_options.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/async_long_running_operation.h"
#include "google/cloud/internal/pagination_range.h"
#include "google/cloud/internal/retry_loop.h"
#include <memory>

namespace google {
namespace cloud {
namespace dialogflow_es_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

EntityTypesConnectionImpl::EntityTypesConnectionImpl(
    std::unique_ptr<google::cloud::BackgroundThreads> background,
    std::shared_ptr<dialogflow_es_internal::EntityTypesStub> stub,
    Options options)
    : background_(std::move(background)),
      stub_(std::move(stub)),
      options_(internal::MergeOptions(
          std::move(options), dialogflow_es_internal::EntityTypesDefaultOptions(
                                  EntityTypesConnection::options()))) {}

StreamRange<google::cloud::dialogflow::v2::EntityType>
EntityTypesConnectionImpl::ListEntityTypes(
    google::cloud::dialogflow::v2::ListEntityTypesRequest request) {
  request.clear_page_token();
  auto& stub = stub_;
  auto retry = std::shared_ptr<dialogflow_es::EntityTypesRetryPolicy const>(
      retry_policy());
  auto backoff = std::shared_ptr<BackoffPolicy const>(backoff_policy());
  auto idempotency = idempotency_policy()->ListEntityTypes(request);
  char const* function_name = __func__;
  return google::cloud::internal::MakePaginationRange<
      StreamRange<google::cloud::dialogflow::v2::EntityType>>(
      std::move(request),
      [stub, retry, backoff, idempotency, function_name](
          google::cloud::dialogflow::v2::ListEntityTypesRequest const& r) {
        return google::cloud::internal::RetryLoop(
            retry->clone(), backoff->clone(), idempotency,
            [stub](grpc::ClientContext& context,
                   google::cloud::dialogflow::v2::ListEntityTypesRequest const&
                       request) {
              return stub->ListEntityTypes(context, request);
            },
            r, function_name);
      },
      [](google::cloud::dialogflow::v2::ListEntityTypesResponse r) {
        std::vector<google::cloud::dialogflow::v2::EntityType> result(
            r.entity_types().size());
        auto& messages = *r.mutable_entity_types();
        std::move(messages.begin(), messages.end(), result.begin());
        return result;
      });
}

StatusOr<google::cloud::dialogflow::v2::EntityType>
EntityTypesConnectionImpl::GetEntityType(
    google::cloud::dialogflow::v2::GetEntityTypeRequest const& request) {
  return google::cloud::internal::RetryLoop(
      retry_policy(), backoff_policy(),
      idempotency_policy()->GetEntityType(request),
      [this](
          grpc::ClientContext& context,
          google::cloud::dialogflow::v2::GetEntityTypeRequest const& request) {
        return stub_->GetEntityType(context, request);
      },
      request, __func__);
}

StatusOr<google::cloud::dialogflow::v2::EntityType>
EntityTypesConnectionImpl::CreateEntityType(
    google::cloud::dialogflow::v2::CreateEntityTypeRequest const& request) {
  return google::cloud::internal::RetryLoop(
      retry_policy(), backoff_policy(),
      idempotency_policy()->CreateEntityType(request),
      [this](grpc::ClientContext& context,
             google::cloud::dialogflow::v2::CreateEntityTypeRequest const&
                 request) { return stub_->CreateEntityType(context, request); },
      request, __func__);
}

StatusOr<google::cloud::dialogflow::v2::EntityType>
EntityTypesConnectionImpl::UpdateEntityType(
    google::cloud::dialogflow::v2::UpdateEntityTypeRequest const& request) {
  return google::cloud::internal::RetryLoop(
      retry_policy(), backoff_policy(),
      idempotency_policy()->UpdateEntityType(request),
      [this](grpc::ClientContext& context,
             google::cloud::dialogflow::v2::UpdateEntityTypeRequest const&
                 request) { return stub_->UpdateEntityType(context, request); },
      request, __func__);
}

Status EntityTypesConnectionImpl::DeleteEntityType(
    google::cloud::dialogflow::v2::DeleteEntityTypeRequest const& request) {
  return google::cloud::internal::RetryLoop(
      retry_policy(), backoff_policy(),
      idempotency_policy()->DeleteEntityType(request),
      [this](grpc::ClientContext& context,
             google::cloud::dialogflow::v2::DeleteEntityTypeRequest const&
                 request) { return stub_->DeleteEntityType(context, request); },
      request, __func__);
}

future<StatusOr<google::cloud::dialogflow::v2::BatchUpdateEntityTypesResponse>>
EntityTypesConnectionImpl::BatchUpdateEntityTypes(
    google::cloud::dialogflow::v2::BatchUpdateEntityTypesRequest const&
        request) {
  auto& stub = stub_;
  return google::cloud::internal::AsyncLongRunningOperation<
      google::cloud::dialogflow::v2::BatchUpdateEntityTypesResponse>(
      background_->cq(), request,
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::cloud::dialogflow::v2::BatchUpdateEntityTypesRequest const&
                 request) {
        return stub->AsyncBatchUpdateEntityTypes(cq, std::move(context),
                                                 request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context), request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context), request);
      },
      &google::cloud::internal::ExtractLongRunningResultResponse<
          google::cloud::dialogflow::v2::BatchUpdateEntityTypesResponse>,
      retry_policy(), backoff_policy(),
      idempotency_policy()->BatchUpdateEntityTypes(request), polling_policy(),
      __func__);
}

future<StatusOr<google::protobuf::Struct>>
EntityTypesConnectionImpl::BatchDeleteEntityTypes(
    google::cloud::dialogflow::v2::BatchDeleteEntityTypesRequest const&
        request) {
  auto& stub = stub_;
  return google::cloud::internal::AsyncLongRunningOperation<
      google::protobuf::Struct>(
      background_->cq(), request,
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::cloud::dialogflow::v2::BatchDeleteEntityTypesRequest const&
                 request) {
        return stub->AsyncBatchDeleteEntityTypes(cq, std::move(context),
                                                 request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context), request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context), request);
      },
      &google::cloud::internal::ExtractLongRunningResultMetadata<
          google::protobuf::Struct>,
      retry_policy(), backoff_policy(),
      idempotency_policy()->BatchDeleteEntityTypes(request), polling_policy(),
      __func__);
}

future<StatusOr<google::protobuf::Struct>>
EntityTypesConnectionImpl::BatchCreateEntities(
    google::cloud::dialogflow::v2::BatchCreateEntitiesRequest const& request) {
  auto& stub = stub_;
  return google::cloud::internal::AsyncLongRunningOperation<
      google::protobuf::Struct>(
      background_->cq(), request,
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::cloud::dialogflow::v2::BatchCreateEntitiesRequest const&
                 request) {
        return stub->AsyncBatchCreateEntities(cq, std::move(context), request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context), request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context), request);
      },
      &google::cloud::internal::ExtractLongRunningResultMetadata<
          google::protobuf::Struct>,
      retry_policy(), backoff_policy(),
      idempotency_policy()->BatchCreateEntities(request), polling_policy(),
      __func__);
}

future<StatusOr<google::protobuf::Struct>>
EntityTypesConnectionImpl::BatchUpdateEntities(
    google::cloud::dialogflow::v2::BatchUpdateEntitiesRequest const& request) {
  auto& stub = stub_;
  return google::cloud::internal::AsyncLongRunningOperation<
      google::protobuf::Struct>(
      background_->cq(), request,
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::cloud::dialogflow::v2::BatchUpdateEntitiesRequest const&
                 request) {
        return stub->AsyncBatchUpdateEntities(cq, std::move(context), request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context), request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context), request);
      },
      &google::cloud::internal::ExtractLongRunningResultMetadata<
          google::protobuf::Struct>,
      retry_policy(), backoff_policy(),
      idempotency_policy()->BatchUpdateEntities(request), polling_policy(),
      __func__);
}

future<StatusOr<google::protobuf::Struct>>
EntityTypesConnectionImpl::BatchDeleteEntities(
    google::cloud::dialogflow::v2::BatchDeleteEntitiesRequest const& request) {
  auto& stub = stub_;
  return google::cloud::internal::AsyncLongRunningOperation<
      google::protobuf::Struct>(
      background_->cq(), request,
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::cloud::dialogflow::v2::BatchDeleteEntitiesRequest const&
                 request) {
        return stub->AsyncBatchDeleteEntities(cq, std::move(context), request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context), request);
      },
      [stub](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context), request);
      },
      &google::cloud::internal::ExtractLongRunningResultMetadata<
          google::protobuf::Struct>,
      retry_policy(), backoff_policy(),
      idempotency_policy()->BatchDeleteEntities(request), polling_policy(),
      __func__);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace dialogflow_es_internal
}  // namespace cloud
}  // namespace google
