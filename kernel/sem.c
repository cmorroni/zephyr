/*
 * Copyright (c) 2010-2016 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 *
 * @brief Kernel semaphore object.
 *
 * The semaphores are of the 'counting' type, i.e. each 'give' operation will
 * increment the internal count by 1, if no thread is pending on it. The 'init'
 * call initializes the count to 'initial_count'. Following multiple 'give'
 * operations, the same number of 'take' operations can be performed without
 * the calling thread having to pend on the semaphore, or the calling task
 * having to poll.
 */

#include <kernel.h>

int z_impl_k_sem_init(struct k_sem *sem, unsigned int initial_count,
		      unsigned int limit)
{
	return 0;
}

void z_impl_k_sem_give(struct k_sem *sem)
{
}

int z_impl_k_sem_take(struct k_sem *sem, k_timeout_t timeout)
{
	return 0;
}
