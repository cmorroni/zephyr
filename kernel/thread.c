/*
 * Copyright (c) 2010-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>

void z_impl_k_busy_wait(u32_t usec_to_wait)
{
}

int z_impl_k_thread_name_set(struct k_thread *thread, const char *value)
{
	return 0;
}

k_tid_t z_impl_k_thread_create(struct k_thread *new_thread,
			      k_thread_stack_t *stack,
			      size_t stack_size, k_thread_entry_t entry,
			      void *p1, void *p2, void *p3,
			      int prio, u32_t options, k_timeout_t delay)
{
	return NULL;
}
