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

#include "google/cloud/baremetalsolution/internal/bare_metal_solution_logging_decorator.h"
#include "google/cloud/internal/log_wrapper.h"
#include "google/cloud/status_or.h"
#include <google/cloud/baremetalsolution/v2/baremetalsolution.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace baremetalsolution_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

BareMetalSolutionLogging::BareMetalSolutionLogging(
    std::shared_ptr<BareMetalSolutionStub> child,
    TracingOptions tracing_options, std::set<std::string> components)
    : child_(std::move(child)),
      tracing_options_(std::move(tracing_options)),
      components_(std::move(components)) {}

StatusOr<google::cloud::baremetalsolution::v2::ListInstancesResponse>
BareMetalSolutionLogging::ListInstances(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::ListInstancesRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::cloud::baremetalsolution::v2::ListInstancesRequest const&
                 request) { return child_->ListInstances(context, request); },
      context, request, __func__, tracing_options_);
}

StatusOr<google::cloud::baremetalsolution::v2::Instance>
BareMetalSolutionLogging::GetInstance(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::GetInstanceRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::cloud::baremetalsolution::v2::GetInstanceRequest const&
                 request) { return child_->GetInstance(context, request); },
      context, request, __func__, tracing_options_);
}

future<StatusOr<google::longrunning::Operation>>
BareMetalSolutionLogging::AsyncResetInstance(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::cloud::baremetalsolution::v2::ResetInstanceRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::cloud::baremetalsolution::v2::ResetInstanceRequest const&
                 request) {
        return child_->AsyncResetInstance(cq, std::move(context), request);
      },
      cq, std::move(context), request, __func__, tracing_options_);
}

StatusOr<google::cloud::baremetalsolution::v2::ListVolumesResponse>
BareMetalSolutionLogging::ListVolumes(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::ListVolumesRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::cloud::baremetalsolution::v2::ListVolumesRequest const&
                 request) { return child_->ListVolumes(context, request); },
      context, request, __func__, tracing_options_);
}

StatusOr<google::cloud::baremetalsolution::v2::Volume>
BareMetalSolutionLogging::GetVolume(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::GetVolumeRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::cloud::baremetalsolution::v2::GetVolumeRequest const&
                 request) { return child_->GetVolume(context, request); },
      context, request, __func__, tracing_options_);
}

future<StatusOr<google::longrunning::Operation>>
BareMetalSolutionLogging::AsyncUpdateVolume(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::cloud::baremetalsolution::v2::UpdateVolumeRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::cloud::baremetalsolution::v2::UpdateVolumeRequest const&
                 request) {
        return child_->AsyncUpdateVolume(cq, std::move(context), request);
      },
      cq, std::move(context), request, __func__, tracing_options_);
}

StatusOr<google::cloud::baremetalsolution::v2::ListNetworksResponse>
BareMetalSolutionLogging::ListNetworks(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::ListNetworksRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::cloud::baremetalsolution::v2::ListNetworksRequest const&
                 request) { return child_->ListNetworks(context, request); },
      context, request, __func__, tracing_options_);
}

StatusOr<google::cloud::baremetalsolution::v2::Network>
BareMetalSolutionLogging::GetNetwork(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::GetNetworkRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::cloud::baremetalsolution::v2::GetNetworkRequest const&
                 request) { return child_->GetNetwork(context, request); },
      context, request, __func__, tracing_options_);
}

StatusOr<
    google::cloud::baremetalsolution::v2::ListSnapshotSchedulePoliciesResponse>
BareMetalSolutionLogging::ListSnapshotSchedulePolicies(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::
        ListSnapshotSchedulePoliciesRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::cloud::baremetalsolution::v2::
                 ListSnapshotSchedulePoliciesRequest const& request) {
        return child_->ListSnapshotSchedulePolicies(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<google::cloud::baremetalsolution::v2::SnapshotSchedulePolicy>
BareMetalSolutionLogging::GetSnapshotSchedulePolicy(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::
        GetSnapshotSchedulePolicyRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::cloud::baremetalsolution::v2::
                 GetSnapshotSchedulePolicyRequest const& request) {
        return child_->GetSnapshotSchedulePolicy(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<google::cloud::baremetalsolution::v2::SnapshotSchedulePolicy>
BareMetalSolutionLogging::CreateSnapshotSchedulePolicy(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::
        CreateSnapshotSchedulePolicyRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::cloud::baremetalsolution::v2::
                 CreateSnapshotSchedulePolicyRequest const& request) {
        return child_->CreateSnapshotSchedulePolicy(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<google::cloud::baremetalsolution::v2::SnapshotSchedulePolicy>
BareMetalSolutionLogging::UpdateSnapshotSchedulePolicy(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::
        UpdateSnapshotSchedulePolicyRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::cloud::baremetalsolution::v2::
                 UpdateSnapshotSchedulePolicyRequest const& request) {
        return child_->UpdateSnapshotSchedulePolicy(context, request);
      },
      context, request, __func__, tracing_options_);
}

Status BareMetalSolutionLogging::DeleteSnapshotSchedulePolicy(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::
        DeleteSnapshotSchedulePolicyRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::cloud::baremetalsolution::v2::
                 DeleteSnapshotSchedulePolicyRequest const& request) {
        return child_->DeleteSnapshotSchedulePolicy(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<google::cloud::baremetalsolution::v2::VolumeSnapshot>
BareMetalSolutionLogging::CreateVolumeSnapshot(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::CreateVolumeSnapshotRequest const&
        request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::cloud::baremetalsolution::v2::
                 CreateVolumeSnapshotRequest const& request) {
        return child_->CreateVolumeSnapshot(context, request);
      },
      context, request, __func__, tracing_options_);
}

future<StatusOr<google::longrunning::Operation>>
BareMetalSolutionLogging::AsyncRestoreVolumeSnapshot(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::cloud::baremetalsolution::v2::RestoreVolumeSnapshotRequest const&
        request) {
  return google::cloud::internal::LogWrapper(
      [this](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::cloud::baremetalsolution::v2::
                 RestoreVolumeSnapshotRequest const& request) {
        return child_->AsyncRestoreVolumeSnapshot(cq, std::move(context),
                                                  request);
      },
      cq, std::move(context), request, __func__, tracing_options_);
}

Status BareMetalSolutionLogging::DeleteVolumeSnapshot(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::DeleteVolumeSnapshotRequest const&
        request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::cloud::baremetalsolution::v2::
                 DeleteVolumeSnapshotRequest const& request) {
        return child_->DeleteVolumeSnapshot(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<google::cloud::baremetalsolution::v2::VolumeSnapshot>
BareMetalSolutionLogging::GetVolumeSnapshot(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::GetVolumeSnapshotRequest const&
        request) {
  return google::cloud::internal::LogWrapper(
      [this](
          grpc::ClientContext& context,
          google::cloud::baremetalsolution::v2::GetVolumeSnapshotRequest const&
              request) { return child_->GetVolumeSnapshot(context, request); },
      context, request, __func__, tracing_options_);
}

StatusOr<google::cloud::baremetalsolution::v2::ListVolumeSnapshotsResponse>
BareMetalSolutionLogging::ListVolumeSnapshots(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::ListVolumeSnapshotsRequest const&
        request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::cloud::baremetalsolution::v2::
                 ListVolumeSnapshotsRequest const& request) {
        return child_->ListVolumeSnapshots(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<google::cloud::baremetalsolution::v2::Lun>
BareMetalSolutionLogging::GetLun(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::GetLunRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](
          grpc::ClientContext& context,
          google::cloud::baremetalsolution::v2::GetLunRequest const& request) {
        return child_->GetLun(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<google::cloud::baremetalsolution::v2::ListLunsResponse>
BareMetalSolutionLogging::ListLuns(
    grpc::ClientContext& context,
    google::cloud::baremetalsolution::v2::ListLunsRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::cloud::baremetalsolution::v2::ListLunsRequest const&
                 request) { return child_->ListLuns(context, request); },
      context, request, __func__, tracing_options_);
}

future<StatusOr<google::longrunning::Operation>>
BareMetalSolutionLogging::AsyncGetOperation(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::longrunning::GetOperationRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::GetOperationRequest const& request) {
        return child_->AsyncGetOperation(cq, std::move(context), request);
      },
      cq, std::move(context), request, __func__, tracing_options_);
}

future<Status> BareMetalSolutionLogging::AsyncCancelOperation(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::longrunning::CancelOperationRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](google::cloud::CompletionQueue& cq,
             std::unique_ptr<grpc::ClientContext> context,
             google::longrunning::CancelOperationRequest const& request) {
        return child_->AsyncCancelOperation(cq, std::move(context), request);
      },
      cq, std::move(context), request, __func__, tracing_options_);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace baremetalsolution_internal
}  // namespace cloud
}  // namespace google
