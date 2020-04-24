/*
 * Copyright (c) 2010-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Kernel thread support
 *
 * This module provides general purpose thread support.
 */

#include <kernel.h>

bool k_is_in_isr(void)
{
	return true;
}

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

void z_init_thread_base(struct _thread_base *thread_base, int priority,
		       u32_t initial_state, unsigned int options)
{
}

/* These spinlock assertion predicates are defined here because having
 * them in spinlock.h is a giant header ordering headache.
 */
#ifdef CONFIG_SPIN_VALIDATE
bool z_spin_lock_valid(struct k_spinlock *l)
{
	return true;
}

bool z_spin_unlock_valid(struct k_spinlock *l)
{
	return true;
}

void z_spin_lock_set_owner(struct k_spinlock *l)
{
}
#endif /* CONFIG_SPIN_VALIDATE */
