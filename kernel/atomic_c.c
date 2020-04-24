/*
 * Copyright (c) 2016 Intel Corporation
 * Copyright (c) 2011-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Atomic ops in pure C
 *
 * This module provides the atomic operators for processors
 * which do not support native atomic operations.
 *
 * The atomic operations are guaranteed to be atomic with respect
 * to interrupt service routines, and to operations performed by peer
 * processors.
 *
 * (originally from x86's atomic.c)
 */

#include <kernel_structs.h>

/**
 *
 * @brief Atomic get primitive
 *
 * @param target memory location to read from
 *
 * This routine provides the atomic get primitive to atomically read
 * a value from <target>. It simply does an ordinary load.  Note that <target>
 * is expected to be aligned to a 4-byte boundary.
 *
 * @return The value read from <target>
 */
atomic_val_t atomic_get(const atomic_t *target)
{
	return *target;
}
