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
// source: google/cloud/datacatalog/v1/policytagmanager.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DATACATALOG_MOCKS_MOCK_POLICY_TAG_MANAGER_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DATACATALOG_MOCKS_MOCK_POLICY_TAG_MANAGER_CONNECTION_H

#include "google/cloud/datacatalog/policy_tag_manager_connection.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace datacatalog_mocks {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/**
 * A class to mock `PolicyTagManagerConnection`.
 *
 * Application developers may want to test their code with simulated responses,
 * including errors, from an object of type `PolicyTagManagerClient`. To do so,
 * construct an object of type `PolicyTagManagerClient` with an instance of this
 * class. Then use the Google Test framework functions to program the behavior
 * of this mock.
 *
 * @see [This example][bq-mock] for how to test your application with
 * GoogleTest. While the example showcases types from the BigQuery library, the
 * underlying principles apply for any pair of `*Client` and `*Connection`.
 *
 * [bq-mock]: @googleapis_dev_link{bigquery,bigquery-read-mock.html}
 */
class MockPolicyTagManagerConnection
    : public datacatalog::PolicyTagManagerConnection {
 public:
  MOCK_METHOD(Options, options, (), (override));

  MOCK_METHOD(
      StatusOr<google::cloud::datacatalog::v1::Taxonomy>, CreateTaxonomy,
      (google::cloud::datacatalog::v1::CreateTaxonomyRequest const& request),
      (override));

  MOCK_METHOD(
      Status, DeleteTaxonomy,
      (google::cloud::datacatalog::v1::DeleteTaxonomyRequest const& request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::datacatalog::v1::Taxonomy>, UpdateTaxonomy,
      (google::cloud::datacatalog::v1::UpdateTaxonomyRequest const& request),
      (override));

  MOCK_METHOD(StreamRange<google::cloud::datacatalog::v1::Taxonomy>,
              ListTaxonomies,
              (google::cloud::datacatalog::v1::ListTaxonomiesRequest request),
              (override));

  MOCK_METHOD(
      StatusOr<google::cloud::datacatalog::v1::Taxonomy>, GetTaxonomy,
      (google::cloud::datacatalog::v1::GetTaxonomyRequest const& request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::datacatalog::v1::PolicyTag>, CreatePolicyTag,
      (google::cloud::datacatalog::v1::CreatePolicyTagRequest const& request),
      (override));

  MOCK_METHOD(
      Status, DeletePolicyTag,
      (google::cloud::datacatalog::v1::DeletePolicyTagRequest const& request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::datacatalog::v1::PolicyTag>, UpdatePolicyTag,
      (google::cloud::datacatalog::v1::UpdatePolicyTagRequest const& request),
      (override));

  MOCK_METHOD(StreamRange<google::cloud::datacatalog::v1::PolicyTag>,
              ListPolicyTags,
              (google::cloud::datacatalog::v1::ListPolicyTagsRequest request),
              (override));

  MOCK_METHOD(
      StatusOr<google::cloud::datacatalog::v1::PolicyTag>, GetPolicyTag,
      (google::cloud::datacatalog::v1::GetPolicyTagRequest const& request),
      (override));

  MOCK_METHOD(StatusOr<google::iam::v1::Policy>, GetIamPolicy,
              (google::iam::v1::GetIamPolicyRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::iam::v1::Policy>, SetIamPolicy,
              (google::iam::v1::SetIamPolicyRequest const& request),
              (override));

  MOCK_METHOD(StatusOr<google::iam::v1::TestIamPermissionsResponse>,
              TestIamPermissions,
              (google::iam::v1::TestIamPermissionsRequest const& request),
              (override));
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace datacatalog_mocks
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DATACATALOG_MOCKS_MOCK_POLICY_TAG_MANAGER_CONNECTION_H
