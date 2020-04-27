/*
 * Copyright (c) 2010-2016 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
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
