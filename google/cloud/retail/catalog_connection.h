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
// source: google/cloud/retail/v2/catalog_service.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_RETAIL_CATALOG_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_RETAIL_CATALOG_CONNECTION_H

#include "google/cloud/retail/catalog_connection_idempotency_policy.h"
#include "google/cloud/retail/internal/catalog_retry_traits.h"
#include "google/cloud/retail/internal/catalog_stub.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/stream_range.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace retail {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

using CatalogServiceRetryPolicy =
    ::google::cloud::internal::TraitBasedRetryPolicy<
        retail_internal::CatalogServiceRetryTraits>;

using CatalogServiceLimitedTimeRetryPolicy =
    ::google::cloud::internal::LimitedTimeRetryPolicy<
        retail_internal::CatalogServiceRetryTraits>;

using CatalogServiceLimitedErrorCountRetryPolicy =
    ::google::cloud::internal::LimitedErrorCountRetryPolicy<
        retail_internal::CatalogServiceRetryTraits>;

/**
 * The `CatalogServiceConnection` object for `CatalogServiceClient`.
 *
 * This interface defines virtual methods for each of the user-facing overload
 * sets in `CatalogServiceClient`. This allows users to inject custom behavior
 * (e.g., with a Google Mock object) when writing tests that use objects of type
 * `CatalogServiceClient`.
 *
 * To create a concrete instance, see `MakeCatalogServiceConnection()`.
 *
 * For mocking, see `retail_mocks::MockCatalogServiceConnection`.
 */
class CatalogServiceConnection {
 public:
  virtual ~CatalogServiceConnection() = 0;

  virtual Options options() { return Options{}; }

  virtual StreamRange<google::cloud::retail::v2::Catalog> ListCatalogs(
      google::cloud::retail::v2::ListCatalogsRequest request);

  virtual StatusOr<google::cloud::retail::v2::Catalog> UpdateCatalog(
      google::cloud::retail::v2::UpdateCatalogRequest const& request);

  virtual Status SetDefaultBranch(
      google::cloud::retail::v2::SetDefaultBranchRequest const& request);

  virtual StatusOr<google::cloud::retail::v2::GetDefaultBranchResponse>
  GetDefaultBranch(
      google::cloud::retail::v2::GetDefaultBranchRequest const& request);
};

/**
 * A factory function to construct an object of type `CatalogServiceConnection`.
 *
 * The returned connection object should not be used directly; instead it
 * should be passed as an argument to the constructor of CatalogServiceClient,
 * and that class used instead.
 *
 * The optional @p opts argument may be used to configure aspects of the
 * returned `CatalogServiceConnection`. Expected options are any of the types in
 * the following option lists:
 *
 * - `google::cloud::CommonOptionList`
 * - `google::cloud::GrpcOptionList`
 * - `google::cloud::retail::CatalogServicePolicyOptionList`
 *
 * @note Unrecognized options will be ignored. To debug issues with options set
 *     `GOOGLE_CLOUD_CPP_ENABLE_CLOG=yes` in the environment and unexpected
 *     options will be logged.
 *
 * @param options (optional) Configure the `CatalogServiceConnection` created by
 * this function.
 */
std::shared_ptr<CatalogServiceConnection> MakeCatalogServiceConnection(
    Options options = {});

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace retail
}  // namespace cloud
}  // namespace google

namespace google {
namespace cloud {
namespace retail_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::shared_ptr<retail::CatalogServiceConnection> MakeCatalogServiceConnection(
    std::shared_ptr<CatalogServiceStub> stub, Options options);

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace retail_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_RETAIL_CATALOG_CONNECTION_H
