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
// source: google/cloud/baremetalsolution/v2/baremetalsolution.proto

#include "google/cloud/baremetalsolution/internal/bare_metal_solution_metadata_decorator.h"
#include "google/cloud/common_options.h"
#include "google/cloud/internal/api_client_header.h"
#include "google/cloud/status_or.h"
#include <google/cloud/baremetalsolution/v2/baremetalsolution.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace baremetalsolution_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

BareMetalSolutionMetadata::BareMetalSolutionMetadata(
    std::shared_ptr<BareMetalSolutionStub> child)
    : child_(std::move(child)),
      api_client_header_(
          google::cloud::internal::ApiClientHeader("generator")) {}

StatusOr<google::cloud::baremetalsolution::v2::ListInstancesResponse>
BareMetalSolutionMetadata::ListInstances(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::ListInstancesRequest const& request) {
  SetMetadata(context, "parent=" + request.parent());
  return child_->ListInstances(context, request);
}

StatusOr<google::cloud::baremetalsolution::v2::Instance>
BareMetalSolutionMetadata::GetInstance(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::GetInstanceRequest const& request) {
  SetMetadata(context, "name=" + request.name());
  return child_->GetInstance(context, request);
}

future<StatusOr<google::longrunning::Operation>>
BareMetalSolutionMetadata::AsyncResetInstance(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::cloud::baremetalsolution::v2::ResetInstanceRequest const& request) {
  SetMetadata(*context, "name=" + request.name());
  return child_->AsyncResetInstance(cq, std::move(context), request);
}

StatusOr<google::cloud::baremetalsolution::v2::ListVolumesResponse>
BareMetalSolutionMetadata::ListVolumes(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::ListVolumesRequest const& request) {
  SetMetadata(context, "parent=" + request.parent());
  return child_->ListVolumes(context, request);
}

StatusOr<google::cloud::baremetalsolution::v2::Volume>
BareMetalSolutionMetadata::GetVolume(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::GetVolumeRequest const& request) {
  SetMetadata(context, "name=" + request.name());
  return child_->GetVolume(context, request);
}

future<StatusOr<google::longrunning::Operation>>
BareMetalSolutionMetadata::AsyncUpdateVolume(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::cloud::baremetalsolution::v2::UpdateVolumeRequest const& request) {
  SetMetadata(*context, "volume.name=" + request.volume().name());
  return child_->AsyncUpdateVolume(cq, std::move(context), request);
}

StatusOr<google::cloud::baremetalsolution::v2::ListNetworksResponse>
BareMetalSolutionMetadata::ListNetworks(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::ListNetworksRequest const& request) {
  SetMetadata(context, "parent=" + request.parent());
  return child_->ListNetworks(context, request);
}

StatusOr<google::cloud::baremetalsolution::v2::Network>
BareMetalSolutionMetadata::GetNetwork(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::GetNetworkRequest const& request) {
  SetMetadata(context, "name=" + request.name());
  return child_->GetNetwork(context, request);
}

StatusOr<
    google::cloud::baremetalsolution::v2::ListSnapshotSchedulePoliciesResponse>
BareMetalSolutionMetadata::ListSnapshotSchedulePolicies(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::
        ListSnapshotSchedulePoliciesRequest const& request) {
  SetMetadata(context, "parent=" + request.parent());
  return child_->ListSnapshotSchedulePolicies(context, request);
}

StatusOr<google::cloud::baremetalsolution::v2::SnapshotSchedulePolicy>
BareMetalSolutionMetadata::GetSnapshotSchedulePolicy(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::
        GetSnapshotSchedulePolicyRequest const& request) {
  SetMetadata(context, "name=" + request.name());
  return child_->GetSnapshotSchedulePolicy(context, request);
}

StatusOr<google::cloud::baremetalsolution::v2::SnapshotSchedulePolicy>
BareMetalSolutionMetadata::CreateSnapshotSchedulePolicy(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::
        CreateSnapshotSchedulePolicyRequest const& request) {
  SetMetadata(context, "parent=" + request.parent());
  return child_->CreateSnapshotSchedulePolicy(context, request);
}

StatusOr<google::cloud::baremetalsolution::v2::SnapshotSchedulePolicy>
BareMetalSolutionMetadata::UpdateSnapshotSchedulePolicy(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::
        UpdateSnapshotSchedulePolicyRequest const& request) {
  SetMetadata(context, "snapshot_schedule_policy.name=" +
                           request.snapshot_schedule_policy().name());
  return child_->UpdateSnapshotSchedulePolicy(context, request);
}

Status BareMetalSolutionMetadata::DeleteSnapshotSchedulePolicy(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::
        DeleteSnapshotSchedulePolicyRequest const& request) {
  SetMetadata(context, "name=" + request.name());
  return child_->DeleteSnapshotSchedulePolicy(context, request);
}

StatusOr<google::cloud::baremetalsolution::v2::VolumeSnapshot>
BareMetalSolutionMetadata::CreateVolumeSnapshot(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::CreateVolumeSnapshotRequest const&
        request) {
  SetMetadata(context, "parent=" + request.parent());
  return child_->CreateVolumeSnapshot(context, request);
}

future<StatusOr<google::longrunning::Operation>>
BareMetalSolutionMetadata::AsyncRestoreVolumeSnapshot(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::cloud::baremetalsolution::v2::RestoreVolumeSnapshotRequest const&
        request) {
  SetMetadata(*context, "volume_snapshot=" + request.volume_snapshot());
  return child_->AsyncRestoreVolumeSnapshot(cq, std::move(context), request);
}

Status BareMetalSolutionMetadata::DeleteVolumeSnapshot(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::DeleteVolumeSnapshotRequest const&
        request) {
  SetMetadata(context, "name=" + request.name());
  return child_->DeleteVolumeSnapshot(context, request);
}

StatusOr<google::cloud::baremetalsolution::v2::VolumeSnapshot>
BareMetalSolutionMetadata::GetVolumeSnapshot(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::GetVolumeSnapshotRequest const&
        request) {
  SetMetadata(context, "name=" + request.name());
  return child_->GetVolumeSnapshot(context, request);
}

StatusOr<google::cloud::baremetalsolution::v2::ListVolumeSnapshotsResponse>
BareMetalSolutionMetadata::ListVolumeSnapshots(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::ListVolumeSnapshotsRequest const&
        request) {
  SetMetadata(context, "parent=" + request.parent());
  return child_->ListVolumeSnapshots(context, request);
}

StatusOr<google::cloud::baremetalsolution::v2::Lun>
BareMetalSolutionMetadata::GetLun(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::GetLunRequest const& request) {
  SetMetadata(context, "name=" + request.name());
  return child_->GetLun(context, request);
}

StatusOr<google::cloud::baremetalsolution::v2::ListLunsResponse>
BareMetalSolutionMetadata::ListLuns(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::ListLunsRequest const& request) {
  SetMetadata(context, "parent=" + request.parent());
  return child_->ListLuns(context, request);
}

future<StatusOr<google::longrunning::Operation>>
BareMetalSolutionMetadata::AsyncGetOperation(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::longrunning::GetOperationRequest const& request) {
  SetMetadata(*context, "name=" + request.name());
  return child_->AsyncGetOperation(cq, std::move(context), request);
}

future<Status> BareMetalSolutionMetadata::AsyncCancelOperation(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::longrunning::CancelOperationRequest const& request) {
  SetMetadata(*context, "name=" + request.name());
  return child_->AsyncCancelOperation(cq, std::move(context), request);
}

void BareMetalSolutionMetadata::SetMetadata(grpc::ClientContext& context,
                                            std::string const& request_params) {
  context.AddMetadata("x-goog-request-params", request_params);
  SetMetadata(context);
}

void BareMetalSolutionMetadata::SetMetadata(grpc::ClientContext& context) {
  context.AddMetadata("x-goog-api-client", api_client_header_);
  auto const& options = internal::CurrentOptions();
  if (options.has<UserProjectOption>()) {
    context.AddMetadata("x-goog-user-project",
                        options.get<UserProjectOption>());
  }
  auto const& authority = options.get<AuthorityOption>();
  if (!authority.empty()) context.set_authority(authority);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace baremetalsolution_internal
}  // namespace cloud
}  // namespace google
