/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "linkerconfig/baseconfig.h"
#include "linkerconfig/variables.h"
#include "testbase.h"

using android::linkerconfig::modules::AsanPath;

TEST(linkerconfig_default_backward_compatibility, common_system_section) {
  MockVariables();

  auto config = android::linkerconfig::contents::CreateBaseConfiguration();

  auto system_section = config.GetSection("system");
  ASSERT_TRUE(system_section);

  auto default_namespace = system_section->GetNamespace("default");
  ASSERT_TRUE(default_namespace);

  ASSERT_TRUE(default_namespace->ContainsPermittedPath("/vendor/framework",
                                                       AsanPath::SAME_PATH));
  ASSERT_TRUE(default_namespace->ContainsPermittedPath("/vendor/app",
                                                       AsanPath::SAME_PATH));
  ASSERT_TRUE(default_namespace->ContainsPermittedPath("/vendor/priv-app",
                                                       AsanPath::SAME_PATH));
  ASSERT_TRUE(default_namespace->ContainsPermittedPath(
      "/system/vendor/framework", AsanPath::SAME_PATH));
  ASSERT_TRUE(default_namespace->ContainsPermittedPath("/system/vendor/app",
                                                       AsanPath::SAME_PATH));
  ASSERT_TRUE(default_namespace->ContainsPermittedPath(
      "/system/vendor/priv-app", AsanPath::SAME_PATH));
  ASSERT_TRUE(default_namespace->ContainsPermittedPath("/odm/framework",
                                                       AsanPath::SAME_PATH));
  ASSERT_TRUE(default_namespace->ContainsPermittedPath("/odm/app",
                                                       AsanPath::SAME_PATH));
  ASSERT_TRUE(default_namespace->ContainsPermittedPath("/odm/priv-app",
                                                       AsanPath::SAME_PATH));

  auto sphal_namespace = system_section->GetNamespace("sphal");
  ASSERT_TRUE(sphal_namespace);

  ASSERT_TRUE(sphal_namespace->ContainsSearchPath("/odm/${LIB}",
                                                  AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(sphal_namespace->ContainsSearchPath("/vendor/${LIB}",
                                                  AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(
      sphal_namespace->ContainsSearchPath("/vendor/${LIB}/hw", AsanPath::NONE));

  ASSERT_TRUE(sphal_namespace->ContainsPermittedPath("/odm/${LIB}",
                                                     AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(sphal_namespace->ContainsPermittedPath("/vendor/${LIB}",
                                                     AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(sphal_namespace->ContainsPermittedPath("/system/vendor/${LIB}",
                                                     AsanPath::NONE));

  auto rs_namespace = system_section->GetNamespace("rs");
  ASSERT_TRUE(rs_namespace);

  ASSERT_TRUE(rs_namespace->ContainsSearchPath("/odm/${LIB}/vndk-sp",
                                               AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(rs_namespace->ContainsSearchPath("/vendor/${LIB}/vndk-sp",
                                               AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(rs_namespace->ContainsSearchPath("/odm/${LIB}",
                                               AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(rs_namespace->ContainsSearchPath("/vendor/${LIB}",
                                               AsanPath::WITH_DATA_ASAN));

  ASSERT_TRUE(rs_namespace->ContainsPermittedPath("/odm/${LIB}",
                                                  AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(rs_namespace->ContainsPermittedPath("/vendor/${LIB}",
                                                  AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(rs_namespace->ContainsPermittedPath("/system/vendor/${LIB}",
                                                  AsanPath::NONE));

  auto vndk_namespace = system_section->GetNamespace("vndk");
  ASSERT_TRUE(vndk_namespace);

  ASSERT_TRUE(vndk_namespace->ContainsSearchPath("/odm/${LIB}/vndk-sp",
                                                 AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(vndk_namespace->ContainsSearchPath("/vendor/${LIB}/vndk-sp",
                                                 AsanPath::WITH_DATA_ASAN));

  ASSERT_TRUE(vndk_namespace->ContainsPermittedPath("/odm/${LIB}/hw",
                                                    AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(vndk_namespace->ContainsPermittedPath("/odm/${LIB}/egl",
                                                    AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(vndk_namespace->ContainsPermittedPath("/vendor/${LIB}/hw",
                                                    AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(vndk_namespace->ContainsPermittedPath("/vendor/${LIB}/egl",
                                                    AsanPath::WITH_DATA_ASAN));
}

TEST(linkerconfig_default_backward_compatibility, common_vendor_section) {
  MockVariables();

  auto config = android::linkerconfig::contents::CreateBaseConfiguration();

  auto vendor_section = config.GetSection("vendor");
  ASSERT_TRUE(vendor_section);

  auto default_namespace = vendor_section->GetNamespace("default");
  ASSERT_TRUE(default_namespace);

  ASSERT_TRUE(default_namespace->ContainsSearchPath("/odm/${LIB}",
                                                    AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(default_namespace->ContainsSearchPath("/vendor/${LIB}",
                                                    AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(default_namespace->ContainsPermittedPath(
      "/odm", AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(default_namespace->ContainsPermittedPath(
      "/vendor", AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(default_namespace->ContainsPermittedPath("/system/vendor",
                                                       AsanPath::NONE));

  auto vndk_namespace = vendor_section->GetNamespace("vndk");
  ASSERT_TRUE(vndk_namespace);

  ASSERT_TRUE(vndk_namespace->ContainsSearchPath("/odm/${LIB}/vndk",
                                                 AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(vndk_namespace->ContainsSearchPath("/odm/${LIB}/vndk-sp",
                                                 AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(vndk_namespace->ContainsSearchPath("/vendor/${LIB}/vndk",
                                                 AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(vndk_namespace->ContainsSearchPath("/vendor/${LIB}/vndk-sp",
                                                 AsanPath::WITH_DATA_ASAN));
}

TEST(linkerconfig_default_backward_compatibility, common_unrestricted_section) {
  MockVariables();

  auto config = android::linkerconfig::contents::CreateBaseConfiguration();

  auto unrestricted_section = config.GetSection("unrestricted");
  ASSERT_TRUE(unrestricted_section);

  auto default_namespace = unrestricted_section->GetNamespace("default");
  ASSERT_TRUE(default_namespace);

  ASSERT_TRUE(default_namespace->ContainsSearchPath("/odm/${LIB}",
                                                    AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(default_namespace->ContainsSearchPath("/vendor/${LIB}",
                                                    AsanPath::WITH_DATA_ASAN));
}

TEST(linkerconfig_default_backward_compatibility, vndk_27) {
  MockVariables();
  android::linkerconfig::modules::Variables::AddValue("ro.vndk.version", "27");

  auto config = android::linkerconfig::contents::CreateBaseConfiguration();

  auto vendor_section = config.GetSection("vendor");
  ASSERT_TRUE(vendor_section);

  auto default_namespace = vendor_section->GetNamespace("default");
  ASSERT_TRUE(default_namespace);

  ASSERT_TRUE(default_namespace->ContainsSearchPath("/vendor/${LIB}/hw",
                                                    AsanPath::WITH_DATA_ASAN));
  ASSERT_TRUE(default_namespace->ContainsSearchPath("/vendor/${LIB}/egl",
                                                    AsanPath::WITH_DATA_ASAN));
}
