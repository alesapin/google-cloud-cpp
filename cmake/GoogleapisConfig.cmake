# ~~~
# Copyright 2021 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ~~~

# Give application developers a hook to configure the version and hash
# downloaded from GitHub.
set(GOOGLE_CLOUD_CPP_GOOGLEAPIS_COMMIT_SHA
    "fbb5dd93b4b94af776b722928d69dacaa7680d5a"
    CACHE STRING "Configure the commit SHA (or tag) for the googleapis protos.")
mark_as_advanced(GOOGLE_CLOUD_CPP_GOOGLEAPIS_SHA)
set(GOOGLE_CLOUD_CPP_GOOGLEAPIS_SHA256
    "47d5742af841543a3a3841fa0ebec31c7a8447a15d6b77a88c6a40fbb198704e"
    CACHE STRING "Configure the SHA256 checksum of the googleapis tarball.")
mark_as_advanced(GOOGLE_CLOUD_CPP_GOOGLEAPIS_SHA256)

set(DOXYGEN_ALIASES
    "googleapis_link{2}=\"[\\1](https://github.com/googleapis/googleapis/blob/${GOOGLE_CLOUD_CPP_GOOGLEAPIS_COMMIT_SHA}/\\2)\""
    "googleapis_reference_link{1}=\"https://github.com/googleapis/googleapis/blob/${GOOGLE_CLOUD_CPP_GOOGLEAPIS_COMMIT_SHA}/\\1\""
)
