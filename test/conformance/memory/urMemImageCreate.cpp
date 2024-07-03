// Copyright (C) 2023 Intel Corporation
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT SPDX-License-Identifier: Apache-2.0 WITH
// LLVM-exception
#include <uur/fixtures.h>
#include <uur/raii.h>

using urMemImageCreateTest = uur::urContextTest;
UUR_INSTANTIATE_DEVICE_TEST_SUITE_P(urMemImageCreateTest);

static ur_image_format_t image_format{UR_IMAGE_CHANNEL_ORDER_RGBA,
                                      UR_IMAGE_CHANNEL_TYPE_SIGNED_INT32};

static ur_image_desc_t image_desc{
    UR_STRUCTURE_TYPE_IMAGE_DESC, ///< [in] type of this structure
    nullptr, ///< [in][optional] pointer to extension-specific structure
    UR_MEM_TYPE_IMAGE3D, ///< [in] memory object type
    1,                   ///< [in] image width
    1,                   ///< [in] image height
    1,                   ///< [in] image depth
    1,                   ///< [in] image array size
    0,                   ///< [in] image row pitch
    0,                   ///< [in] image slice pitch
    0,                   ///< [in] number of MIP levels
    0                    ///< [in] number of samples
};

using urMemImageCreateTestWith1DMemoryTypeParam =
    uur::urContextTestWithParam<ur_mem_type_t>;

UUR_TEST_SUITE_P(urMemImageCreateTestWith1DMemoryTypeParam,
                 ::testing::Values(UR_MEM_TYPE_IMAGE1D,
                                   UR_MEM_TYPE_IMAGE1D_ARRAY),
                 uur::deviceTestWithParamPrinter<ur_mem_type_t>);

TEST_P(urMemImageCreateTestWith1DMemoryTypeParam, Success) {
  ur_image_desc_t image_desc_with_param{
      UR_STRUCTURE_TYPE_IMAGE_DESC, ///< [in] type of this structure
      nullptr,    ///< [in][optional] pointer to extension-specific structure
      getParam(), ///< [in] memory object type
      1,          ///< [in] image width
      0,          ///< [in] image height
      0,          ///< [in] image depth
      1,          ///< [in] image array size
      0,          ///< [in] image row pitch
      0,          ///< [in] image slice pitch
      0,          ///< [in] number of MIP levels
      0           ///< [in] number of samples
  };

  ur_mem_handle_t image_handle = nullptr;
  ASSERT_SUCCESS(urMemImageCreate(context, UR_MEM_FLAG_READ_WRITE,
                                  &image_format, &image_desc_with_param,
                                  nullptr, &image_handle));
  ASSERT_NE(nullptr, image_handle);
  ASSERT_SUCCESS(urMemRelease(image_handle));
}

using urMemImageCreateTestWith2DMemoryTypeParam =
    uur::urContextTestWithParam<ur_mem_type_t>;

UUR_TEST_SUITE_P(urMemImageCreateTestWith2DMemoryTypeParam,
                 ::testing::Values(UR_MEM_TYPE_IMAGE2D,
                                   UR_MEM_TYPE_IMAGE2D_ARRAY),
                 uur::deviceTestWithParamPrinter<ur_mem_type_t>);

TEST_P(urMemImageCreateTestWith2DMemoryTypeParam, Success) {
  ur_image_desc_t image_desc_with_param{
      UR_STRUCTURE_TYPE_IMAGE_DESC, ///< [in] type of this structure
      nullptr,    ///< [in][optional] pointer to extension-specific structure
      getParam(), ///< [in] memory object type
      1,          ///< [in] image width
      1,          ///< [in] image height
      0,          ///< [in] image depth
      1,          ///< [in] image array size
      0,          ///< [in] image row pitch
      0,          ///< [in] image slice pitch
      0,          ///< [in] number of MIP levels
      0           ///< [in] number of samples
  };

  ur_mem_handle_t image_handle = nullptr;
  ASSERT_SUCCESS(urMemImageCreate(context, UR_MEM_FLAG_READ_WRITE,
                                  &image_format, &image_desc_with_param,
                                  nullptr, &image_handle));
  ASSERT_NE(nullptr, image_handle);
  ASSERT_SUCCESS(urMemRelease(image_handle));
}

TEST_P(urMemImageCreateTest, SuccessWith3DImageType) {
  ur_image_desc_t image_desc_with_param{
      UR_STRUCTURE_TYPE_IMAGE_DESC, ///< [in] type of this structure
      nullptr, ///< [in][optional] pointer to extension-specific structure
      UR_MEM_TYPE_IMAGE3D, ///< [in] memory object type
      1,                   ///< [in] image width
      1,                   ///< [in] image height
      1,                   ///< [in] image depth
      1,                   ///< [in] image array size
      0,                   ///< [in] image row pitch
      0,                   ///< [in] image slice pitch
      0,                   ///< [in] number of MIP levels
      0                    ///< [in] number of samples
  };

  ur_mem_handle_t image_handle = nullptr;
  ASSERT_SUCCESS(urMemImageCreate(context, UR_MEM_FLAG_READ_WRITE,
                                  &image_format, &image_desc_with_param,
                                  nullptr, &image_handle));
  ASSERT_NE(nullptr, image_handle);
  ASSERT_SUCCESS(urMemRelease(image_handle));
}

TEST_P(urMemImageCreateTest, InvalidNullHandleContext) {
  ur_mem_handle_t image_handle = nullptr;
  ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_NULL_HANDLE,
                   urMemImageCreate(nullptr, UR_MEM_FLAG_READ_WRITE,
                                    &image_format, &image_desc, nullptr,
                                    &image_handle));
}

TEST_P(urMemImageCreateTest, InvalidEnumerationFlags) {
  ur_mem_handle_t image_handle = nullptr;
  ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_ENUMERATION,
                   urMemImageCreate(context, UR_MEM_FLAG_FORCE_UINT32,
                                    &image_format, &image_desc, nullptr,
                                    &image_handle));
}

TEST_P(urMemImageCreateTest, InvalidNullPointerBuffer) {
  ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_NULL_POINTER,
                   urMemImageCreate(context, UR_MEM_FLAG_READ_WRITE,
                                    &image_format, &image_desc, nullptr,
                                    nullptr));
}

TEST_P(urMemImageCreateTest, InvalidNullPointerImageDesc) {
  ur_mem_handle_t image_handle = nullptr;
  ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_NULL_POINTER,
                   urMemImageCreate(context, UR_MEM_FLAG_READ_WRITE,
                                    &image_format, nullptr, nullptr,
                                    &image_handle));
}

TEST_P(urMemImageCreateTest, InvalidNullPointerImageFormat) {
  ur_mem_handle_t image_handle = nullptr;
  ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_NULL_POINTER,
                   urMemImageCreate(context, UR_MEM_FLAG_READ_WRITE, nullptr,
                                    &image_desc, nullptr, &image_handle));
}

TEST_P(urMemImageCreateTest, InvalidSize) {

  ur_mem_handle_t image_handle = nullptr;

  ur_image_desc_t invalid_image_desc = image_desc;
  invalid_image_desc.width = std::numeric_limits<size_t>::max();

  ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_IMAGE_SIZE,
                   urMemImageCreate(context, UR_MEM_FLAG_READ_WRITE,
                                    &image_format, &invalid_image_desc, nullptr,
                                    &image_handle));

  invalid_image_desc = image_desc;
  invalid_image_desc.height = std::numeric_limits<size_t>::max();

  ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_IMAGE_SIZE,
                   urMemImageCreate(context, UR_MEM_FLAG_READ_WRITE,
                                    &image_format, &invalid_image_desc, nullptr,
                                    &image_handle));

  invalid_image_desc = image_desc;
  invalid_image_desc.depth = std::numeric_limits<size_t>::max();

  ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_IMAGE_SIZE,
                   urMemImageCreate(context, UR_MEM_FLAG_READ_WRITE,
                                    &image_format, &invalid_image_desc, nullptr,
                                    &image_handle));
}

TEST_P(urMemImageCreateTest, InvalidImageDescStype) {
  ur_mem_handle_t image_handle = nullptr;
  ur_image_desc_t invalid_image_desc = image_desc;
  invalid_image_desc.stype = UR_STRUCTURE_TYPE_FORCE_UINT32;
  ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_IMAGE_FORMAT_DESCRIPTOR,
                   urMemImageCreate(context, UR_MEM_FLAG_READ_WRITE,
                                    &image_format, &invalid_image_desc, nullptr,
                                    &image_handle));
}

TEST_P(urMemImageCreateTest, InvalidImageDescType) {
  ur_mem_handle_t image_handle = nullptr;

  ur_image_desc_t invalid_image_desc = image_desc;
  invalid_image_desc.type = UR_MEM_TYPE_FORCE_UINT32;

  ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_IMAGE_FORMAT_DESCRIPTOR,
                   urMemImageCreate(context, UR_MEM_FLAG_READ_WRITE,
                                    &image_format, &invalid_image_desc, nullptr,
                                    &image_handle));
}

TEST_P(urMemImageCreateTest, InvalidImageDescNumMipLevel) {
  ur_mem_handle_t image_handle = nullptr;

  ur_image_desc_t invalid_image_desc = image_desc;
  invalid_image_desc.numMipLevel = 1; /* Must be 0 */

  ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_IMAGE_FORMAT_DESCRIPTOR,
                   urMemImageCreate(context, UR_MEM_FLAG_READ_WRITE,
                                    &image_format, &invalid_image_desc, nullptr,
                                    &image_handle));
}

TEST_P(urMemImageCreateTest, InvalidImageDescNumSamples) {
  ur_mem_handle_t image_handle = nullptr;

  ur_image_desc_t invalid_image_desc = image_desc;
  invalid_image_desc.numSamples = 1; /* Must be 0 */

  ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_IMAGE_FORMAT_DESCRIPTOR,
                   urMemImageCreate(context, UR_MEM_FLAG_READ_WRITE,
                                    &image_format, &invalid_image_desc, nullptr,
                                    &image_handle));
}

TEST_P(urMemImageCreateTest, InvalidImageDescRowPitch) {
  ur_mem_handle_t image_handle = nullptr;

  ur_image_desc_t invalid_image_desc = image_desc;
  invalid_image_desc.rowPitch = 1; /* Must be 0 if pHost is NULL */

  ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_IMAGE_FORMAT_DESCRIPTOR,
                   urMemImageCreate(context, UR_MEM_FLAG_READ_WRITE,
                                    &image_format, &invalid_image_desc, nullptr,
                                    &image_handle));
}

TEST_P(urMemImageCreateTest, InvalidImageDescSlicePitch) {
  ur_mem_handle_t image_handle = nullptr;

  ur_image_desc_t invalid_image_desc = image_desc;
  invalid_image_desc.slicePitch = 1; /* Must be 0 if pHost is NULL */

  ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_IMAGE_FORMAT_DESCRIPTOR,
                   urMemImageCreate(context, UR_MEM_FLAG_READ_WRITE,
                                    &image_format, &invalid_image_desc, nullptr,
                                    &image_handle));
}

using urMemImageCreateWithHostPtrFlagsTest =
    uur::urContextTestWithParam<ur_mem_flag_t>;

UUR_TEST_SUITE_P(urMemImageCreateWithHostPtrFlagsTest,
                 ::testing::Values(UR_MEM_FLAG_ALLOC_COPY_HOST_POINTER,
                                   UR_MEM_FLAG_USE_HOST_POINTER),
                 uur::deviceTestWithParamPrinter<ur_mem_flag_t>);

TEST_P(urMemImageCreateWithHostPtrFlagsTest, Success) {
  uur::raii::Mem host_ptr_buffer = nullptr;
  ASSERT_SUCCESS(urMemImageCreate(context, UR_MEM_FLAG_ALLOC_HOST_POINTER,
                                  &image_format, &image_desc, nullptr,
                                  host_ptr_buffer.ptr()));

  uur::raii::Mem image_handle = nullptr;
  ASSERT_SUCCESS(urMemImageCreate(context, getParam(), &image_format,
                                  &image_desc, host_ptr_buffer.ptr(),
                                  image_handle.ptr()));
  ASSERT_NE(nullptr, image_handle.ptr());
}

TEST_P(urMemImageCreateWithHostPtrFlagsTest, InvalidHostPtr) {
  ur_mem_handle_t image_handle = nullptr;
  ASSERT_EQ_RESULT(UR_RESULT_ERROR_INVALID_HOST_PTR,
                   urMemImageCreate(context, getParam(), &image_format,
                                    &image_desc, nullptr, &image_handle));
}
