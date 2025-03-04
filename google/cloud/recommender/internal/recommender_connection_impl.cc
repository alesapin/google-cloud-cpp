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
// source: google/cloud/recommender/v1/recommender_service.proto

#include "google/cloud/recommender/internal/recommender_connection_impl.h"
#include "google/cloud/recommender/internal/recommender_option_defaults.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/common_options.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/pagination_range.h"
#include "google/cloud/internal/retry_loop.h"
#include <memory>

namespace google {
namespace cloud {
namespace recommender_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

RecommenderConnectionImpl::RecommenderConnectionImpl(
    std::unique_ptr<google::cloud::BackgroundThreads> background,
    std::shared_ptr<recommender_internal::RecommenderStub> stub,
    Options options)
    : background_(std::move(background)),
      stub_(std::move(stub)),
      options_(internal::MergeOptions(
          std::move(options), recommender_internal::RecommenderDefaultOptions(
                                  RecommenderConnection::options()))) {}

StreamRange<google::cloud::recommender::v1::Insight>
RecommenderConnectionImpl::ListInsights(
    google::cloud::recommender::v1::ListInsightsRequest request) {
  request.clear_page_token();
  auto& stub = stub_;
  auto retry = std::shared_ptr<recommender::RecommenderRetryPolicy const>(
      retry_policy());
  auto backoff = std::shared_ptr<BackoffPolicy const>(backoff_policy());
  auto idempotency = idempotency_policy()->ListInsights(request);
  char const* function_name = __func__;
  return google::cloud::internal::MakePaginationRange<
      StreamRange<google::cloud::recommender::v1::Insight>>(
      std::move(request),
      [stub, retry, backoff, idempotency, function_name](
          google::cloud::recommender::v1::ListInsightsRequest const& r) {
        return google::cloud::internal::RetryLoop(
            retry->clone(), backoff->clone(), idempotency,
            [stub](grpc::ClientContext& context,
                   google::cloud::recommender::v1::ListInsightsRequest const&
                       request) {
              return stub->ListInsights(context, request);
            },
            r, function_name);
      },
      [](google::cloud::recommender::v1::ListInsightsResponse r) {
        std::vector<google::cloud::recommender::v1::Insight> result(
            r.insights().size());
        auto& messages = *r.mutable_insights();
        std::move(messages.begin(), messages.end(), result.begin());
        return result;
      });
}

StatusOr<google::cloud::recommender::v1::Insight>
RecommenderConnectionImpl::GetInsight(
    google::cloud::recommender::v1::GetInsightRequest const& request) {
  return google::cloud::internal::RetryLoop(
      retry_policy(), backoff_policy(),
      idempotency_policy()->GetInsight(request),
      [this](grpc::ClientContext& context,
             google::cloud::recommender::v1::GetInsightRequest const& request) {
        return stub_->GetInsight(context, request);
      },
      request, __func__);
}

StatusOr<google::cloud::recommender::v1::Insight>
RecommenderConnectionImpl::MarkInsightAccepted(
    google::cloud::recommender::v1::MarkInsightAcceptedRequest const& request) {
  return google::cloud::internal::RetryLoop(
      retry_policy(), backoff_policy(),
      idempotency_policy()->MarkInsightAccepted(request),
      [this](grpc::ClientContext& context,
             google::cloud::recommender::v1::MarkInsightAcceptedRequest const&
                 request) {
        return stub_->MarkInsightAccepted(context, request);
      },
      request, __func__);
}

StreamRange<google::cloud::recommender::v1::Recommendation>
RecommenderConnectionImpl::ListRecommendations(
    google::cloud::recommender::v1::ListRecommendationsRequest request) {
  request.clear_page_token();
  auto& stub = stub_;
  auto retry = std::shared_ptr<recommender::RecommenderRetryPolicy const>(
      retry_policy());
  auto backoff = std::shared_ptr<BackoffPolicy const>(backoff_policy());
  auto idempotency = idempotency_policy()->ListRecommendations(request);
  char const* function_name = __func__;
  return google::cloud::internal::MakePaginationRange<
      StreamRange<google::cloud::recommender::v1::Recommendation>>(
      std::move(request),
      [stub, retry, backoff, idempotency, function_name](
          google::cloud::recommender::v1::ListRecommendationsRequest const& r) {
        return google::cloud::internal::RetryLoop(
            retry->clone(), backoff->clone(), idempotency,
            [stub](grpc::ClientContext& context,
                   google::cloud::recommender::v1::
                       ListRecommendationsRequest const& request) {
              return stub->ListRecommendations(context, request);
            },
            r, function_name);
      },
      [](google::cloud::recommender::v1::ListRecommendationsResponse r) {
        std::vector<google::cloud::recommender::v1::Recommendation> result(
            r.recommendations().size());
        auto& messages = *r.mutable_recommendations();
        std::move(messages.begin(), messages.end(), result.begin());
        return result;
      });
}

StatusOr<google::cloud::recommender::v1::Recommendation>
RecommenderConnectionImpl::GetRecommendation(
    google::cloud::recommender::v1::GetRecommendationRequest const& request) {
  return google::cloud::internal::RetryLoop(
      retry_policy(), backoff_policy(),
      idempotency_policy()->GetRecommendation(request),
      [this](grpc::ClientContext& context,
             google::cloud::recommender::v1::GetRecommendationRequest const&
                 request) {
        return stub_->GetRecommendation(context, request);
      },
      request, __func__);
}

StatusOr<google::cloud::recommender::v1::Recommendation>
RecommenderConnectionImpl::MarkRecommendationClaimed(
    google::cloud::recommender::v1::MarkRecommendationClaimedRequest const&
        request) {
  return google::cloud::internal::RetryLoop(
      retry_policy(), backoff_policy(),
      idempotency_policy()->MarkRecommendationClaimed(request),
      [this](grpc::ClientContext& context,
             google::cloud::recommender::v1::
                 MarkRecommendationClaimedRequest const& request) {
        return stub_->MarkRecommendationClaimed(context, request);
      },
      request, __func__);
}

StatusOr<google::cloud::recommender::v1::Recommendation>
RecommenderConnectionImpl::MarkRecommendationSucceeded(
    google::cloud::recommender::v1::MarkRecommendationSucceededRequest const&
        request) {
  return google::cloud::internal::RetryLoop(
      retry_policy(), backoff_policy(),
      idempotency_policy()->MarkRecommendationSucceeded(request),
      [this](grpc::ClientContext& context,
             google::cloud::recommender::v1::
                 MarkRecommendationSucceededRequest const& request) {
        return stub_->MarkRecommendationSucceeded(context, request);
      },
      request, __func__);
}

StatusOr<google::cloud::recommender::v1::Recommendation>
RecommenderConnectionImpl::MarkRecommendationFailed(
    google::cloud::recommender::v1::MarkRecommendationFailedRequest const&
        request) {
  return google::cloud::internal::RetryLoop(
      retry_policy(), backoff_policy(),
      idempotency_policy()->MarkRecommendationFailed(request),
      [this](
          grpc::ClientContext& context,
          google::cloud::recommender::v1::MarkRecommendationFailedRequest const&
              request) {
        return stub_->MarkRecommendationFailed(context, request);
      },
      request, __func__);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace recommender_internal
}  // namespace cloud
}  // namespace google
