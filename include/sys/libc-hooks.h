/*
 * Copyright (c) 2018, Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_SYS_LIBC_HOOKS_H_
#define ZEPHYR_INCLUDE_SYS_LIBC_HOOKS_H_

#include <toolchain.h>
#include <stdio.h>
#include <stddef.h>

/*
 * Private header for specifying accessory functions to the C library internals
 * that need to call into the kernel as system calls
 */

/* Minimal libc */

__syscall int zephyr_fputc(int c, FILE * stream);

__syscall size_t zephyr_fwrite(const void *_MLIBC_RESTRICT ptr, size_t size,
				size_t nitems, FILE *_MLIBC_RESTRICT stream);
#include <syscalls/libc-hooks.h>

#endif /* ZEPHYR_INCLUDE_SYS_LIBC_HOOKS_H_ */
