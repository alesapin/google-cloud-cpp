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
// source: google/cloud/dialogflow/v2/conversation_profile.proto

#include "google/cloud/dialogflow_es/internal/conversation_profiles_stub.h"
#include "google/cloud/grpc_error_delegate.h"
#include "google/cloud/status_or.h"
#include <google/cloud/dialogflow/v2/conversation_profile.grpc.pb.h>
#include <google/longrunning/operations.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace dialogflow_es_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

ConversationProfilesStub::~ConversationProfilesStub() = default;

StatusOr<google::cloud::dialogflow::v2::ListConversationProfilesResponse>
DefaultConversationProfilesStub::ListConversationProfiles(
    grpc::ClientContext& client_context,
    google::cloud::dialogflow::v2::ListConversationProfilesRequest const&
        request) {
  google::cloud::dialogflow::v2::ListConversationProfilesResponse response;
  auto status =
      grpc_stub_->ListConversationProfiles(&client_context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::dialogflow::v2::ConversationProfile>
DefaultConversationProfilesStub::GetConversationProfile(
    grpc::ClientContext& client_context,
    google::cloud::dialogflow::v2::GetConversationProfileRequest const&
        request) {
  google::cloud::dialogflow::v2::ConversationProfile response;
  auto status =
      grpc_stub_->GetConversationProfile(&client_context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::dialogflow::v2::ConversationProfile>
DefaultConversationProfilesStub::CreateConversationProfile(
    grpc::ClientContext& client_context,
    google::cloud::dialogflow::v2::CreateConversationProfileRequest const&
        request) {
  google::cloud::dialogflow::v2::ConversationProfile response;
  auto status = grpc_stub_->CreateConversationProfile(&client_context, request,
                                                      &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::dialogflow::v2::ConversationProfile>
DefaultConversationProfilesStub::UpdateConversationProfile(
    grpc::ClientContext& client_context,
    google::cloud::dialogflow::v2::UpdateConversationProfileRequest const&
        request) {
  google::cloud::dialogflow::v2::ConversationProfile response;
  auto status = grpc_stub_->UpdateConversationProfile(&client_context, request,
                                                      &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

Status DefaultConversationProfilesStub::DeleteConversationProfile(
    grpc::ClientContext& client_context,
    google::cloud::dialogflow::v2::DeleteConversationProfileRequest const&
        request) {
  google::protobuf::Empty response;
  auto status = grpc_stub_->DeleteConversationProfile(&client_context, request,
                                                      &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return google::cloud::Status();
}

future<StatusOr<google::longrunning::Operation>>
DefaultConversationProfilesStub::AsyncSetSuggestionFeatureConfig(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::cloud::dialogflow::v2::SetSuggestionFeatureConfigRequest const&
        request) {
  return cq.MakeUnaryRpc(
      [this](grpc::ClientContext* context,
             google::cloud::dialogflow::v2::
                 SetSuggestionFeatureConfigRequest const& request,
             grpc::CompletionQueue* cq) {
        return grpc_stub_->AsyncSetSuggestionFeatureConfig(context, request,
                                                           cq);
      },
      request, std::move(context));
}

future<StatusOr<google::longrunning::Operation>>
DefaultConversationProfilesStub::AsyncClearSuggestionFeatureConfig(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::cloud::dialogflow::v2::ClearSuggestionFeatureConfigRequest const&
        request) {
  return cq.MakeUnaryRpc(
      [this](grpc::ClientContext* context,
             google::cloud::dialogflow::v2::
                 ClearSuggestionFeatureConfigRequest const& request,
             grpc::CompletionQueue* cq) {
        return grpc_stub_->AsyncClearSuggestionFeatureConfig(context, request,
                                                             cq);
      },
      request, std::move(context));
}

future<StatusOr<google::longrunning::Operation>>
DefaultConversationProfilesStub::AsyncGetOperation(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::longrunning::GetOperationRequest const& request) {
  return cq.MakeUnaryRpc(
      [this](grpc::ClientContext* context,
             google::longrunning::GetOperationRequest const& request,
             grpc::CompletionQueue* cq) {
        return operations_->AsyncGetOperation(context, request, cq);
      },
      request, std::move(context));
}

future<Status> DefaultConversationProfilesStub::AsyncCancelOperation(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::longrunning::CancelOperationRequest const& request) {
  return cq
      .MakeUnaryRpc(
          [this](grpc::ClientContext* context,
                 google::longrunning::CancelOperationRequest const& request,
                 grpc::CompletionQueue* cq) {
            return operations_->AsyncCancelOperation(context, request, cq);
          },
          request, std::move(context))
      .then([](future<StatusOr<google::protobuf::Empty>> f) {
        return f.get().status();
      });
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace dialogflow_es_internal
}  // namespace cloud
}  // namespace google
