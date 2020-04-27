/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_POSIX_SYS_TYPES_H_
#define ZEPHYR_INCLUDE_POSIX_SYS_TYPES_H_

#ifndef CONFIG_ARCH_POSIX
#include <sys/types.h>
#endif

#include <kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

/* time related attributes */
#ifndef CONFIG_NEWLIB_LIBC
#ifndef __clockid_t_defined
typedef u32_t clockid_t;
#endif
#endif /*CONFIG_NEWLIB_LIBC */
#ifndef __timer_t_defined
typedef unsigned long timer_t;
#endif

#ifdef __cplusplus
}
#endif

#endif	/* ZEPHYR_INCLUDE_POSIX_SYS_TYPES_H_ */
