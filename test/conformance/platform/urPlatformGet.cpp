// Copyright (C) 2022-2023 Intel Corporation
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM Exceptions.
// See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "fixtures.h"

using urPlatformGetTest = uur::platform::urTest;

TEST_F(urPlatformGetTest, Success) {
    uint32_t count;
    ASSERT_SUCCESS(urPlatformGet(0, nullptr, &count));
    ASSERT_NE(count, 0);
    std::vector<ur_platform_handle_t> platforms(count);
    ASSERT_SUCCESS(urPlatformGet(count, platforms.data(), nullptr));
    for (auto platform : platforms) {
        ASSERT_NE(nullptr, platform);
    }
}

TEST_F(urPlatformGetTest, InvalidNumEntries) {
    uint32_t count;
    ASSERT_SUCCESS(urPlatformGet(0, nullptr, &count));
    std::vector<ur_platform_handle_t> platforms(count);
    ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_SIZE,
                     urPlatformGet(0, platforms.data(), nullptr));
}
