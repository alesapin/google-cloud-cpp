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
// source: google/container/v1/cluster_service.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CONTAINER_CLUSTER_MANAGER_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CONTAINER_CLUSTER_MANAGER_CONNECTION_H

#include "google/cloud/container/cluster_manager_connection_idempotency_policy.h"
#include "google/cloud/container/internal/cluster_manager_retry_traits.h"
#include "google/cloud/container/internal/cluster_manager_stub.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/stream_range.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace container {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

using ClusterManagerRetryPolicy =
    ::google::cloud::internal::TraitBasedRetryPolicy<
        container_internal::ClusterManagerRetryTraits>;

using ClusterManagerLimitedTimeRetryPolicy =
    ::google::cloud::internal::LimitedTimeRetryPolicy<
        container_internal::ClusterManagerRetryTraits>;

using ClusterManagerLimitedErrorCountRetryPolicy =
    ::google::cloud::internal::LimitedErrorCountRetryPolicy<
        container_internal::ClusterManagerRetryTraits>;

/**
 * The `ClusterManagerConnection` object for `ClusterManagerClient`.
 *
 * This interface defines virtual methods for each of the user-facing overload
 * sets in `ClusterManagerClient`. This allows users to inject custom behavior
 * (e.g., with a Google Mock object) when writing tests that use objects of type
 * `ClusterManagerClient`.
 *
 * To create a concrete instance, see `MakeClusterManagerConnection()`.
 *
 * For mocking, see `container_mocks::MockClusterManagerConnection`.
 */
class ClusterManagerConnection {
 public:
  virtual ~ClusterManagerConnection() = 0;

  virtual Options options() { return Options{}; }

  virtual StatusOr<google::container::v1::ListClustersResponse> ListClusters(
      google::container::v1::ListClustersRequest const& request);

  virtual StatusOr<google::container::v1::Cluster> GetCluster(
      google::container::v1::GetClusterRequest const& request);

  virtual StatusOr<google::container::v1::Operation> CreateCluster(
      google::container::v1::CreateClusterRequest const& request);

  virtual StatusOr<google::container::v1::Operation> UpdateCluster(
      google::container::v1::UpdateClusterRequest const& request);

  virtual StatusOr<google::container::v1::Operation> UpdateNodePool(
      google::container::v1::UpdateNodePoolRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetNodePoolAutoscaling(
      google::container::v1::SetNodePoolAutoscalingRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetLoggingService(
      google::container::v1::SetLoggingServiceRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetMonitoringService(
      google::container::v1::SetMonitoringServiceRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetAddonsConfig(
      google::container::v1::SetAddonsConfigRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetLocations(
      google::container::v1::SetLocationsRequest const& request);

  virtual StatusOr<google::container::v1::Operation> UpdateMaster(
      google::container::v1::UpdateMasterRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetMasterAuth(
      google::container::v1::SetMasterAuthRequest const& request);

  virtual StatusOr<google::container::v1::Operation> DeleteCluster(
      google::container::v1::DeleteClusterRequest const& request);

  virtual StatusOr<google::container::v1::ListOperationsResponse>
  ListOperations(google::container::v1::ListOperationsRequest const& request);

  virtual StatusOr<google::container::v1::Operation> GetOperation(
      google::container::v1::GetOperationRequest const& request);

  virtual Status CancelOperation(
      google::container::v1::CancelOperationRequest const& request);

  virtual StatusOr<google::container::v1::ServerConfig> GetServerConfig(
      google::container::v1::GetServerConfigRequest const& request);

  virtual StatusOr<google::container::v1::GetJSONWebKeysResponse>
  GetJSONWebKeys(google::container::v1::GetJSONWebKeysRequest const& request);

  virtual StatusOr<google::container::v1::ListNodePoolsResponse> ListNodePools(
      google::container::v1::ListNodePoolsRequest const& request);

  virtual StatusOr<google::container::v1::NodePool> GetNodePool(
      google::container::v1::GetNodePoolRequest const& request);

  virtual StatusOr<google::container::v1::Operation> CreateNodePool(
      google::container::v1::CreateNodePoolRequest const& request);

  virtual StatusOr<google::container::v1::Operation> DeleteNodePool(
      google::container::v1::DeleteNodePoolRequest const& request);

  virtual StatusOr<google::container::v1::Operation> RollbackNodePoolUpgrade(
      google::container::v1::RollbackNodePoolUpgradeRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetNodePoolManagement(
      google::container::v1::SetNodePoolManagementRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetLabels(
      google::container::v1::SetLabelsRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetLegacyAbac(
      google::container::v1::SetLegacyAbacRequest const& request);

  virtual StatusOr<google::container::v1::Operation> StartIPRotation(
      google::container::v1::StartIPRotationRequest const& request);

  virtual StatusOr<google::container::v1::Operation> CompleteIPRotation(
      google::container::v1::CompleteIPRotationRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetNodePoolSize(
      google::container::v1::SetNodePoolSizeRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetNetworkPolicy(
      google::container::v1::SetNetworkPolicyRequest const& request);

  virtual StatusOr<google::container::v1::Operation> SetMaintenancePolicy(
      google::container::v1::SetMaintenancePolicyRequest const& request);

  virtual StreamRange<google::container::v1::UsableSubnetwork>
  ListUsableSubnetworks(
      google::container::v1::ListUsableSubnetworksRequest request);
};

/**
 * A factory function to construct an object of type `ClusterManagerConnection`.
 *
 * The returned connection object should not be used directly; instead it
 * should be passed as an argument to the constructor of ClusterManagerClient,
 * and that class used instead.
 *
 * The optional @p opts argument may be used to configure aspects of the
 * returned `ClusterManagerConnection`. Expected options are any of the types in
 * the following option lists:
 *
 * - `google::cloud::CommonOptionList`
 * - `google::cloud::GrpcOptionList`
 * - `google::cloud::container::ClusterManagerPolicyOptionList`
 *
 * @note Unrecognized options will be ignored. To debug issues with options set
 *     `GOOGLE_CLOUD_CPP_ENABLE_CLOG=yes` in the environment and unexpected
 *     options will be logged.
 *
 * @param options (optional) Configure the `ClusterManagerConnection` created by
 * this function.
 */
std::shared_ptr<ClusterManagerConnection> MakeClusterManagerConnection(
    Options options = {});

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace container
}  // namespace cloud
}  // namespace google

namespace google {
namespace cloud {
namespace container_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::shared_ptr<container::ClusterManagerConnection>
MakeClusterManagerConnection(std::shared_ptr<ClusterManagerStub> stub,
                             Options options);

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace container_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CONTAINER_CLUSTER_MANAGER_CONNECTION_H
