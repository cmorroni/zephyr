/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/** @file
 *
 * @brief Per-thread errno accessor function
 *
 * Allow accessing the errno for the current thread without involving the
 * context switching.
 */

#include <kernel.h>

/*
 * Define _k_neg_eagain for use in assembly files as errno.h is
 * not assembly language safe.
 * FIXME: wastes 4 bytes
 */
const int _k_neg_eagain = -EAGAIN;

int *z_impl_z_errno(void)
{
	return 0;
}
