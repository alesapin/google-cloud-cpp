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
// source: google/cloud/dialogflow/cx/v3/version.proto

#include "google/cloud/dialogflow_cx/versions_connection_idempotency_policy.h"
#include "absl/memory/memory.h"
#include <memory>

namespace google {
namespace cloud {
namespace dialogflow_cx {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

using ::google::cloud::Idempotency;

VersionsConnectionIdempotencyPolicy::~VersionsConnectionIdempotencyPolicy() =
    default;

namespace {
class DefaultVersionsConnectionIdempotencyPolicy
    : public VersionsConnectionIdempotencyPolicy {
 public:
  ~DefaultVersionsConnectionIdempotencyPolicy() override = default;

  /// Create a new copy of this object.
  std::unique_ptr<VersionsConnectionIdempotencyPolicy> clone() const override {
    return absl::make_unique<DefaultVersionsConnectionIdempotencyPolicy>(*this);
  }

  Idempotency ListVersions(
      google::cloud::dialogflow::cx::v3::ListVersionsRequest) override {
    return Idempotency::kIdempotent;
  }

  Idempotency GetVersion(
      google::cloud::dialogflow::cx::v3::GetVersionRequest const&) override {
    return Idempotency::kIdempotent;
  }

  Idempotency CreateVersion(
      google::cloud::dialogflow::cx::v3::CreateVersionRequest const&) override {
    return Idempotency::kNonIdempotent;
  }

  Idempotency UpdateVersion(
      google::cloud::dialogflow::cx::v3::UpdateVersionRequest const&) override {
    return Idempotency::kNonIdempotent;
  }

  Idempotency DeleteVersion(
      google::cloud::dialogflow::cx::v3::DeleteVersionRequest const&) override {
    return Idempotency::kNonIdempotent;
  }

  Idempotency LoadVersion(
      google::cloud::dialogflow::cx::v3::LoadVersionRequest const&) override {
    return Idempotency::kNonIdempotent;
  }

  Idempotency CompareVersions(
      google::cloud::dialogflow::cx::v3::CompareVersionsRequest const&)
      override {
    return Idempotency::kNonIdempotent;
  }
};
}  // namespace

std::unique_ptr<VersionsConnectionIdempotencyPolicy>
MakeDefaultVersionsConnectionIdempotencyPolicy() {
  return absl::make_unique<DefaultVersionsConnectionIdempotencyPolicy>();
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace dialogflow_cx
}  // namespace cloud
}  // namespace google
