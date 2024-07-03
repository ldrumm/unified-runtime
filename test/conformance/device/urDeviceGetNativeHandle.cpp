// Copyright (C) 2022-2023 Intel Corporation
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT SPDX-License-Identifier: Apache-2.0 WITH
// LLVM-exception
#include <uur/fixtures.h>

using urDeviceGetNativeHandleTest = uur::urAllDevicesTest;

TEST_F(urDeviceGetNativeHandleTest, Success) {
  for (auto device : devices) {
    ur_native_handle_t native_handle = nullptr;
    if (auto error = urDeviceGetNativeHandle(device, &native_handle)) {
      ASSERT_EQ_RESULT(UR_RESULT_ERROR_UNSUPPORTED_FEATURE, error);
    }
  }
}

TEST_F(urDeviceGetNativeHandleTest, InvalidNullHandleDevice) {
  ur_native_handle_t native_handle = nullptr;
  ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_NULL_HANDLE,
                   urDeviceGetNativeHandle(nullptr, &native_handle));
}

TEST_F(urDeviceGetNativeHandleTest, InvalidNullPointerNativeDevice) {
  for (auto device : devices) {
    ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_NULL_POINTER,
                     urDeviceGetNativeHandle(device, nullptr));
  }
}
