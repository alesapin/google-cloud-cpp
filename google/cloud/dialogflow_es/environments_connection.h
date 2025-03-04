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
// source: google/cloud/dialogflow/v2/environment.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DIALOGFLOW_ES_ENVIRONMENTS_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DIALOGFLOW_ES_ENVIRONMENTS_CONNECTION_H

#include "google/cloud/dialogflow_es/environments_connection_idempotency_policy.h"
#include "google/cloud/dialogflow_es/internal/environments_retry_traits.h"
#include "google/cloud/dialogflow_es/internal/environments_stub.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/stream_range.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace dialogflow_es {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

using EnvironmentsRetryPolicy =
    ::google::cloud::internal::TraitBasedRetryPolicy<
        dialogflow_es_internal::EnvironmentsRetryTraits>;

using EnvironmentsLimitedTimeRetryPolicy =
    ::google::cloud::internal::LimitedTimeRetryPolicy<
        dialogflow_es_internal::EnvironmentsRetryTraits>;

using EnvironmentsLimitedErrorCountRetryPolicy =
    ::google::cloud::internal::LimitedErrorCountRetryPolicy<
        dialogflow_es_internal::EnvironmentsRetryTraits>;

/**
 * The `EnvironmentsConnection` object for `EnvironmentsClient`.
 *
 * This interface defines virtual methods for each of the user-facing overload
 * sets in `EnvironmentsClient`. This allows users to inject custom behavior
 * (e.g., with a Google Mock object) when writing tests that use objects of type
 * `EnvironmentsClient`.
 *
 * To create a concrete instance, see `MakeEnvironmentsConnection()`.
 *
 * For mocking, see `dialogflow_es_mocks::MockEnvironmentsConnection`.
 */
class EnvironmentsConnection {
 public:
  virtual ~EnvironmentsConnection() = 0;

  virtual Options options() { return Options{}; }

  virtual StreamRange<google::cloud::dialogflow::v2::Environment>
  ListEnvironments(
      google::cloud::dialogflow::v2::ListEnvironmentsRequest request);

  virtual StatusOr<google::cloud::dialogflow::v2::Environment> GetEnvironment(
      google::cloud::dialogflow::v2::GetEnvironmentRequest const& request);

  virtual StatusOr<google::cloud::dialogflow::v2::Environment>
  CreateEnvironment(
      google::cloud::dialogflow::v2::CreateEnvironmentRequest const& request);

  virtual StatusOr<google::cloud::dialogflow::v2::Environment>
  UpdateEnvironment(
      google::cloud::dialogflow::v2::UpdateEnvironmentRequest const& request);

  virtual Status DeleteEnvironment(
      google::cloud::dialogflow::v2::DeleteEnvironmentRequest const& request);

  virtual StreamRange<google::cloud::dialogflow::v2::EnvironmentHistory::Entry>
  GetEnvironmentHistory(
      google::cloud::dialogflow::v2::GetEnvironmentHistoryRequest request);
};

/**
 * A factory function to construct an object of type `EnvironmentsConnection`.
 *
 * The returned connection object should not be used directly; instead it
 * should be passed as an argument to the constructor of EnvironmentsClient,
 * and that class used instead.
 *
 * The optional @p opts argument may be used to configure aspects of the
 * returned `EnvironmentsConnection`. Expected options are any of the types in
 * the following option lists:
 *
 * - `google::cloud::CommonOptionList`
 * - `google::cloud::GrpcOptionList`
 * - `google::cloud::dialogflow_es::EnvironmentsPolicyOptionList`
 *
 * @note Unrecognized options will be ignored. To debug issues with options set
 *     `GOOGLE_CLOUD_CPP_ENABLE_CLOG=yes` in the environment and unexpected
 *     options will be logged.
 *
 * @param options (optional) Configure the `EnvironmentsConnection` created by
 * this function.
 */
std::shared_ptr<EnvironmentsConnection> MakeEnvironmentsConnection(
    Options options = {});

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace dialogflow_es
}  // namespace cloud
}  // namespace google

namespace google {
namespace cloud {
namespace dialogflow_es_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::shared_ptr<dialogflow_es::EnvironmentsConnection>
MakeEnvironmentsConnection(std::shared_ptr<EnvironmentsStub> stub,
                           Options options);

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace dialogflow_es_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DIALOGFLOW_ES_ENVIRONMENTS_CONNECTION_H
