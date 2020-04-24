/*
 * Copyright (c) 2019 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Internal kernel APIs implemented at the architecture layer.
 *
 * Not all architecture-specific defines are here, APIs that are used
 * by public functions and macros are defined in include/sys/arch_interface.h.
 *
 * For all inline functions prototyped here, the implementation is expected
 * to be provided by arch/ARCH/include/kernel_arch_func.h
 */
#ifndef ZEPHYR_KERNEL_INCLUDE_KERNEL_ARCH_INTERFACE_H_
#define ZEPHYR_KERNEL_INCLUDE_KERNEL_ARCH_INTERFACE_H_

#ifndef _ASMLANGUAGE

#ifdef __cplusplus
extern "C" {
#endif

/* Include arch-specific inline function implementation */
#include <kernel_arch_func.h>

#ifdef __cplusplus
}
#endif

#endif /* _ASMLANGUAGE */

#endif /* ZEPHYR_KERNEL_INCLUDE_KERNEL_ARCH_INTERFACE_H_ */
