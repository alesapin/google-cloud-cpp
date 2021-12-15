// Copyright 2020 Google LLC
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
// source: google/iam/credentials/v1/iamcredentials.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_IAM_IAM_CREDENTIALS_CLIENT_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_IAM_IAM_CREDENTIALS_CLIENT_H

#include "google/cloud/iam/iam_credentials_connection.h"
#include "google/cloud/future.h"
#include "google/cloud/options.h"
#include "google/cloud/polling_policy.h"
#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <google/protobuf/duration.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace iam {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

///
/// A service account is a special type of Google account that belongs to your
/// application or a virtual machine (VM), instead of to an individual end user.
/// Your application assumes the identity of the service account to call Google
/// APIs, so that the users aren't directly involved.
///
/// Service account credentials are used to temporarily assume the identity
/// of the service account. Supported credential types include OAuth 2.0 access
/// tokens, OpenID Connect ID tokens, self-signed JSON Web Tokens (JWTs), and
/// more.
///
/// @par Equality
///
/// Instances of this class created via copy-construction or copy-assignment
/// always compare equal. Instances created with equal
/// `std::shared_ptr<*Connection>` objects compare equal. Objects that compare
/// equal share the same underlying resources.
///
/// @par Performance
///
/// Creating a new instance of this class is a relatively expensive operation,
/// new objects establish new connections to the service. In contrast,
/// copy-construction, move-construction, and the corresponding assignment
/// operations are relatively efficient as the copies share all underlying
/// resources.
///
/// @par Thread Safety
///
/// Concurrent access to different instances of this class, even if they compare
/// equal, is guaranteed to work. Two or more threads operating on the same
/// instance of this class is not guaranteed to work. Since copy-construction
/// and move-construction is a relatively efficient operation, consider using
/// such a copy when using this class from multiple threads.
///
class IAMCredentialsClient {
 public:
  explicit IAMCredentialsClient(
      std::shared_ptr<IAMCredentialsConnection> connection,
      Options options = {});
  ~IAMCredentialsClient();

  //@{
  // @name Copy and move support
  IAMCredentialsClient(IAMCredentialsClient const&) = default;
  IAMCredentialsClient& operator=(IAMCredentialsClient const&) = default;
  IAMCredentialsClient(IAMCredentialsClient&&) = default;
  IAMCredentialsClient& operator=(IAMCredentialsClient&&) = default;
  //@}

  //@{
  // @name Equality
  friend bool operator==(IAMCredentialsClient const& a,
                         IAMCredentialsClient const& b) {
    return a.connection_ == b.connection_;
  }
  friend bool operator!=(IAMCredentialsClient const& a,
                         IAMCredentialsClient const& b) {
    return !(a == b);
  }
  //@}

  ///
  /// Generates an OAuth 2.0 access token for a service account.
  ///
  /// @param name  Required. The resource name of the service account for which
  /// the credentials
  ///  are requested, in the following format:
  ///  `projects/-/serviceAccounts/{ACCOUNT_EMAIL_OR_UNIQUEID}`. The `-`
  ///  wildcard character is required; replacing it with a project ID is
  ///  invalid.
  /// @param delegates  The sequence of service accounts in a delegation chain.
  /// Each service
  ///  account must be granted the `roles/iam.serviceAccountTokenCreator` role
  ///  on its next service account in the chain. The last service account in the
  ///  chain must be granted the `roles/iam.serviceAccountTokenCreator` role
  ///  on the service account that is specified in the `name` field of the
  ///  request.
  ///  The delegates must have the following format:
  ///  `projects/-/serviceAccounts/{ACCOUNT_EMAIL_OR_UNIQUEID}`. The `-`
  ///  wildcard character is required; replacing it with a project ID is
  ///  invalid.
  /// @param scope  Required. Code to identify the scopes to be included in the
  /// OAuth 2.0 access token.
  ///  See https://developers.google.com/identity/protocols/googlescopes for
  ///  more information. At least one value required.
  /// @param lifetime  The desired lifetime duration of the access token in
  /// seconds.
  ///  Must be set to a value less than or equal to 3600 (1 hour). If a value is
  ///  not specified, the token's lifetime will be set to a default value of one
  ///  hour.
  /// @param options  Optional. Operation options.
  /// @return
  /// @googleapis_link{google::iam::credentials::v1::GenerateAccessTokenResponse,google/iam/credentials/v1/common.proto#L72}
  ///
  /// [google.iam.credentials.v1.GenerateAccessTokenRequest]:
  /// @googleapis_reference_link{google/iam/credentials/v1/common.proto#L35}
  /// [google.iam.credentials.v1.GenerateAccessTokenResponse]:
  /// @googleapis_reference_link{google/iam/credentials/v1/common.proto#L72}
  ///
  StatusOr<google::iam::credentials::v1::GenerateAccessTokenResponse>
  GenerateAccessToken(std::string const& name,
                      std::vector<std::string> const& delegates,
                      std::vector<std::string> const& scope,
                      google::protobuf::Duration const& lifetime,
                      Options options = {});

  ///
  /// Generates an OAuth 2.0 access token for a service account.
  ///
  /// @param request
  /// @googleapis_link{google::iam::credentials::v1::GenerateAccessTokenRequest,google/iam/credentials/v1/common.proto#L35}
  /// @param options  Optional. Operation options.
  /// @return
  /// @googleapis_link{google::iam::credentials::v1::GenerateAccessTokenResponse,google/iam/credentials/v1/common.proto#L72}
  ///
  /// [google.iam.credentials.v1.GenerateAccessTokenRequest]:
  /// @googleapis_reference_link{google/iam/credentials/v1/common.proto#L35}
  /// [google.iam.credentials.v1.GenerateAccessTokenResponse]:
  /// @googleapis_reference_link{google/iam/credentials/v1/common.proto#L72}
  ///
  StatusOr<google::iam::credentials::v1::GenerateAccessTokenResponse>
  GenerateAccessToken(
      google::iam::credentials::v1::GenerateAccessTokenRequest const& request,
      Options options = {});

  ///
  /// Generates an OpenID Connect ID token for a service account.
  ///
  /// @param name  Required. The resource name of the service account for which
  /// the credentials
  ///  are requested, in the following format:
  ///  `projects/-/serviceAccounts/{ACCOUNT_EMAIL_OR_UNIQUEID}`. The `-`
  ///  wildcard character is required; replacing it with a project ID is
  ///  invalid.
  /// @param delegates  The sequence of service accounts in a delegation chain.
  /// Each service
  ///  account must be granted the `roles/iam.serviceAccountTokenCreator` role
  ///  on its next service account in the chain. The last service account in the
  ///  chain must be granted the `roles/iam.serviceAccountTokenCreator` role
  ///  on the service account that is specified in the `name` field of the
  ///  request.
  ///  The delegates must have the following format:
  ///  `projects/-/serviceAccounts/{ACCOUNT_EMAIL_OR_UNIQUEID}`. The `-`
  ///  wildcard character is required; replacing it with a project ID is
  ///  invalid.
  /// @param audience  Required. The audience for the token, such as the API or
  /// account that this token
  ///  grants access to.
  /// @param include_email  Include the service account email in the token. If
  /// set to `true`, the
  ///  token will contain `email` and `email_verified` claims.
  /// @param options  Optional. Operation options.
  /// @return
  /// @googleapis_link{google::iam::credentials::v1::GenerateIdTokenResponse,google/iam/credentials/v1/common.proto#L186}
  ///
  /// [google.iam.credentials.v1.GenerateIdTokenRequest]:
  /// @googleapis_reference_link{google/iam/credentials/v1/common.proto#L153}
  /// [google.iam.credentials.v1.GenerateIdTokenResponse]:
  /// @googleapis_reference_link{google/iam/credentials/v1/common.proto#L186}
  ///
  StatusOr<google::iam::credentials::v1::GenerateIdTokenResponse>
  GenerateIdToken(std::string const& name,
                  std::vector<std::string> const& delegates,
                  std::string const& audience, bool include_email,
                  Options options = {});

  ///
  /// Generates an OpenID Connect ID token for a service account.
  ///
  /// @param request
  /// @googleapis_link{google::iam::credentials::v1::GenerateIdTokenRequest,google/iam/credentials/v1/common.proto#L153}
  /// @param options  Optional. Operation options.
  /// @return
  /// @googleapis_link{google::iam::credentials::v1::GenerateIdTokenResponse,google/iam/credentials/v1/common.proto#L186}
  ///
  /// [google.iam.credentials.v1.GenerateIdTokenRequest]:
  /// @googleapis_reference_link{google/iam/credentials/v1/common.proto#L153}
  /// [google.iam.credentials.v1.GenerateIdTokenResponse]:
  /// @googleapis_reference_link{google/iam/credentials/v1/common.proto#L186}
  ///
  StatusOr<google::iam::credentials::v1::GenerateIdTokenResponse>
  GenerateIdToken(
      google::iam::credentials::v1::GenerateIdTokenRequest const& request,
      Options options = {});

  ///
  /// Signs a blob using a service account's system-managed private key.
  ///
  /// @param name  Required. The resource name of the service account for which
  /// the credentials
  ///  are requested, in the following format:
  ///  `projects/-/serviceAccounts/{ACCOUNT_EMAIL_OR_UNIQUEID}`. The `-`
  ///  wildcard character is required; replacing it with a project ID is
  ///  invalid.
  /// @param delegates  The sequence of service accounts in a delegation chain.
  /// Each service
  ///  account must be granted the `roles/iam.serviceAccountTokenCreator` role
  ///  on its next service account in the chain. The last service account in the
  ///  chain must be granted the `roles/iam.serviceAccountTokenCreator` role
  ///  on the service account that is specified in the `name` field of the
  ///  request.
  ///  The delegates must have the following format:
  ///  `projects/-/serviceAccounts/{ACCOUNT_EMAIL_OR_UNIQUEID}`. The `-`
  ///  wildcard character is required; replacing it with a project ID is
  ///  invalid.
  /// @param payload  Required. The bytes to sign.
  /// @param options  Optional. Operation options.
  /// @return
  /// @googleapis_link{google::iam::credentials::v1::SignBlobResponse,google/iam/credentials/v1/common.proto#L109}
  ///
  /// [google.iam.credentials.v1.SignBlobRequest]:
  /// @googleapis_reference_link{google/iam/credentials/v1/common.proto#L81}
  /// [google.iam.credentials.v1.SignBlobResponse]:
  /// @googleapis_reference_link{google/iam/credentials/v1/common.proto#L109}
  ///
  StatusOr<google::iam::credentials::v1::SignBlobResponse> SignBlob(
      std::string const& name, std::vector<std::string> const& delegates,
      std::string const& payload, Options options = {});

  ///
  /// Signs a blob using a service account's system-managed private key.
  ///
  /// @param request
  /// @googleapis_link{google::iam::credentials::v1::SignBlobRequest,google/iam/credentials/v1/common.proto#L81}
  /// @param options  Optional. Operation options.
  /// @return
  /// @googleapis_link{google::iam::credentials::v1::SignBlobResponse,google/iam/credentials/v1/common.proto#L109}
  ///
  /// [google.iam.credentials.v1.SignBlobRequest]:
  /// @googleapis_reference_link{google/iam/credentials/v1/common.proto#L81}
  /// [google.iam.credentials.v1.SignBlobResponse]:
  /// @googleapis_reference_link{google/iam/credentials/v1/common.proto#L109}
  ///
  StatusOr<google::iam::credentials::v1::SignBlobResponse> SignBlob(
      google::iam::credentials::v1::SignBlobRequest const& request,
      Options options = {});

  ///
  /// Signs a JWT using a service account's system-managed private key.
  ///
  /// @param name  Required. The resource name of the service account for which
  /// the credentials
  ///  are requested, in the following format:
  ///  `projects/-/serviceAccounts/{ACCOUNT_EMAIL_OR_UNIQUEID}`. The `-`
  ///  wildcard character is required; replacing it with a project ID is
  ///  invalid.
  /// @param delegates  The sequence of service accounts in a delegation chain.
  /// Each service
  ///  account must be granted the `roles/iam.serviceAccountTokenCreator` role
  ///  on its next service account in the chain. The last service account in the
  ///  chain must be granted the `roles/iam.serviceAccountTokenCreator` role
  ///  on the service account that is specified in the `name` field of the
  ///  request.
  ///  The delegates must have the following format:
  ///  `projects/-/serviceAccounts/{ACCOUNT_EMAIL_OR_UNIQUEID}`. The `-`
  ///  wildcard character is required; replacing it with a project ID is
  ///  invalid.
  /// @param payload  Required. The JWT payload to sign: a JSON object that
  /// contains a JWT Claims Set.
  /// @param options  Optional. Operation options.
  /// @return
  /// @googleapis_link{google::iam::credentials::v1::SignJwtResponse,google/iam/credentials/v1/common.proto#L145}
  ///
  /// [google.iam.credentials.v1.SignJwtRequest]:
  /// @googleapis_reference_link{google/iam/credentials/v1/common.proto#L117}
  /// [google.iam.credentials.v1.SignJwtResponse]:
  /// @googleapis_reference_link{google/iam/credentials/v1/common.proto#L145}
  ///
  StatusOr<google::iam::credentials::v1::SignJwtResponse> SignJwt(
      std::string const& name, std::vector<std::string> const& delegates,
      std::string const& payload, Options options = {});

  ///
  /// Signs a JWT using a service account's system-managed private key.
  ///
  /// @param request
  /// @googleapis_link{google::iam::credentials::v1::SignJwtRequest,google/iam/credentials/v1/common.proto#L117}
  /// @param options  Optional. Operation options.
  /// @return
  /// @googleapis_link{google::iam::credentials::v1::SignJwtResponse,google/iam/credentials/v1/common.proto#L145}
  ///
  /// [google.iam.credentials.v1.SignJwtRequest]:
  /// @googleapis_reference_link{google/iam/credentials/v1/common.proto#L117}
  /// [google.iam.credentials.v1.SignJwtResponse]:
  /// @googleapis_reference_link{google/iam/credentials/v1/common.proto#L145}
  ///
  StatusOr<google::iam::credentials::v1::SignJwtResponse> SignJwt(
      google::iam::credentials::v1::SignJwtRequest const& request,
      Options options = {});

 private:
  std::shared_ptr<IAMCredentialsConnection> connection_;
  Options options_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
namespace gcpcxxV1 = GOOGLE_CLOUD_CPP_NS;  // NOLINT(misc-unused-alias-decls)
}  // namespace iam
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_IAM_IAM_CREDENTIALS_CLIENT_H
