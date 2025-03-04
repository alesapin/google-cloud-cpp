#!/usr/bin/env bash
#
# Copyright 2020 Google LLC
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

set -euo pipefail

source "$(dirname "$0")/../../../lib/init.sh"
source module ci/lib/io.sh
source module ci/etc/integration-tests-config.sh
source module ci/etc/quickstart-config.sh

io::log_h2 "Using CMake version"
cmake --version

io::log_h2 "Update or install dependencies"
# vcpkg needs this
brew list --versions pkg-config || brew install pkg-config

# Fetch vcpkg at the specified hash.
vcpkg_dir="${HOME}/vcpkg-quickstart"
mkdir -p "${vcpkg_dir}"
io::log "Downloading vcpkg into ${vcpkg_dir}..."
VCPKG_COMMIT="$(<ci/etc/vcpkg-commit.txt)"
ci/retry-command.sh 3 120 curl -sSL "https://github.com/microsoft/vcpkg/archive/${VCPKG_COMMIT}.tar.gz" |
  tar -C "${vcpkg_dir}" --strip-components=1 -zxf -
(
  cd "${vcpkg_dir}"
  env VCPKG_ROOT="${vcpkg_dir}" CC="ccache cc" CXX="ccache c++" \
    "${PROJECT_ROOT}/ci/retry-command.sh" 3 120 ./bootstrap-vcpkg.sh
  ./vcpkg remove --outdated --recurse
  ./vcpkg install google-cloud-cpp
)

export NINJA_STATUS="T+%es [%f/%t] "
cmake_flags=(
  "-DCMAKE_TOOLCHAIN_FILE=${vcpkg_dir}/scripts/buildsystems/vcpkg.cmake"
)

build_quickstart() {
  local -r library="$1"
  local -r source_dir="google/cloud/${library}/quickstart"
  local -r binary_dir="cmake-out/quickstart-${library}"
  local cmake
  cmake="$("${vcpkg_dir}/vcpkg" "--feature-flags=-manifests" fetch cmake)"
  local ninja
  ninja="$("${vcpkg_dir}/vcpkg" "--feature-flags=-manifests" fetch ninja)"

  io::log_h2 "Configure CMake for ${library}'s quickstart"
  "${cmake}" "-GNinja" "-DCMAKE_MAKE_PROGRAM=${ninja}" \
    "-H${source_dir}" "-B${binary_dir}" "${cmake_flags[@]}"

  echo
  io::log_h2 "Compiling ${library}'s quickstart"
  "${cmake}" --build "${binary_dir}"
}

errors=""
for library in $(quickstart::libraries); do
  io::log_h2 "Building ${library}'s quickstart"
  if ! build_quickstart "${library}"; then
    io::log_red "Building ${library}'s quickstart failed"
    errors="${errors} ${library}"
  else
    io::log_green "Building ${library}'s quickstart was successful"
  fi
done

if [[ -z "${errors}" ]]; then
  io::log_green "All quickstart builds were successful"
else
  io::log_red "Build failed for ${errors}"
  exit 1
fi
