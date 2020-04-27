/*
 * Copyright (c) 2017, Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#ifndef ZEPHYR_INCLUDE_SYSCALL_H_
#define ZEPHYR_INCLUDE_SYSCALL_H_

#include <stdbool.h>

#ifndef _ASMLANGUAGE

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Indicate whether the CPU is currently in user mode
 *
 * @return true if the CPU is currently running with user permissions
 */
static inline bool _is_user_context(void)
{
	return false;
}

#ifdef __cplusplus
}
#endif

#endif /* _ASMLANGUAGE */

#endif
