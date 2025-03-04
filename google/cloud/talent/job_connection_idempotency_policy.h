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
// source: google/cloud/talent/v4/job_service.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_TALENT_JOB_CONNECTION_IDEMPOTENCY_POLICY_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_TALENT_JOB_CONNECTION_IDEMPOTENCY_POLICY_H

#include "google/cloud/idempotency.h"
#include "google/cloud/internal/retry_policy.h"
#include "google/cloud/version.h"
#include <google/cloud/talent/v4/job_service.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace talent {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class JobServiceConnectionIdempotencyPolicy {
 public:
  virtual ~JobServiceConnectionIdempotencyPolicy() = 0;

  /// Create a new copy of this object.
  virtual std::unique_ptr<JobServiceConnectionIdempotencyPolicy> clone()
      const = 0;

  virtual google::cloud::Idempotency CreateJob(
      google::cloud::talent::v4::CreateJobRequest const& request) = 0;

  virtual google::cloud::Idempotency BatchCreateJobs(
      google::cloud::talent::v4::BatchCreateJobsRequest const& request) = 0;

  virtual google::cloud::Idempotency GetJob(
      google::cloud::talent::v4::GetJobRequest const& request) = 0;

  virtual google::cloud::Idempotency UpdateJob(
      google::cloud::talent::v4::UpdateJobRequest const& request) = 0;

  virtual google::cloud::Idempotency BatchUpdateJobs(
      google::cloud::talent::v4::BatchUpdateJobsRequest const& request) = 0;

  virtual google::cloud::Idempotency DeleteJob(
      google::cloud::talent::v4::DeleteJobRequest const& request) = 0;

  virtual google::cloud::Idempotency BatchDeleteJobs(
      google::cloud::talent::v4::BatchDeleteJobsRequest const& request) = 0;

  virtual google::cloud::Idempotency ListJobs(
      google::cloud::talent::v4::ListJobsRequest request) = 0;

  virtual google::cloud::Idempotency SearchJobs(
      google::cloud::talent::v4::SearchJobsRequest const& request) = 0;

  virtual google::cloud::Idempotency SearchJobsForAlert(
      google::cloud::talent::v4::SearchJobsRequest const& request) = 0;
};

std::unique_ptr<JobServiceConnectionIdempotencyPolicy>
MakeDefaultJobServiceConnectionIdempotencyPolicy();

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace talent
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_TALENT_JOB_CONNECTION_IDEMPOTENCY_POLICY_H
