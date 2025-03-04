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
// source: google/cloud/assuredworkloads/v1/assuredworkloads.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_ASSUREDWORKLOADS_INTERNAL_ASSURED_WORKLOADS_AUTH_DECORATOR_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_ASSUREDWORKLOADS_INTERNAL_ASSURED_WORKLOADS_AUTH_DECORATOR_H

#include "google/cloud/assuredworkloads/internal/assured_workloads_stub.h"
#include "google/cloud/internal/unified_grpc_credentials.h"
#include "google/cloud/version.h"
#include <google/longrunning/operations.grpc.pb.h>
#include <memory>
#include <set>
#include <string>

namespace google {
namespace cloud {
namespace assuredworkloads_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class AssuredWorkloadsServiceAuth : public AssuredWorkloadsServiceStub {
 public:
  ~AssuredWorkloadsServiceAuth() override = default;
  AssuredWorkloadsServiceAuth(
      std::shared_ptr<google::cloud::internal::GrpcAuthenticationStrategy> auth,
      std::shared_ptr<AssuredWorkloadsServiceStub> child);

  future<StatusOr<google::longrunning::Operation>> AsyncCreateWorkload(
      google::cloud::CompletionQueue& cq,
      std::unique_ptr<grpc::ClientContext> context,
      google::cloud::assuredworkloads::v1::CreateWorkloadRequest const& request)
      override;

  StatusOr<google::cloud::assuredworkloads::v1::Workload> UpdateWorkload(
      grpc::ClientContext& context,
      google::cloud::assuredworkloads::v1::UpdateWorkloadRequest const& request)
      override;

  Status DeleteWorkload(
      grpc::ClientContext& context,
      google::cloud::assuredworkloads::v1::DeleteWorkloadRequest const& request)
      override;

  StatusOr<google::cloud::assuredworkloads::v1::Workload> GetWorkload(
      grpc::ClientContext& context,
      google::cloud::assuredworkloads::v1::GetWorkloadRequest const& request)
      override;

  StatusOr<google::cloud::assuredworkloads::v1::ListWorkloadsResponse>
  ListWorkloads(grpc::ClientContext& context,
                google::cloud::assuredworkloads::v1::ListWorkloadsRequest const&
                    request) override;

  future<StatusOr<google::longrunning::Operation>> AsyncGetOperation(
      google::cloud::CompletionQueue& cq,
      std::unique_ptr<grpc::ClientContext> context,
      google::longrunning::GetOperationRequest const& request) override;

  future<Status> AsyncCancelOperation(
      google::cloud::CompletionQueue& cq,
      std::unique_ptr<grpc::ClientContext> context,
      google::longrunning::CancelOperationRequest const& request) override;

 private:
  std::shared_ptr<google::cloud::internal::GrpcAuthenticationStrategy> auth_;
  std::shared_ptr<AssuredWorkloadsServiceStub> child_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace assuredworkloads_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_ASSUREDWORKLOADS_INTERNAL_ASSURED_WORKLOADS_AUTH_DECORATOR_H
