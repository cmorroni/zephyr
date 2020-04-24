/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <kernel_internal.h>

/* the only struct z_kernel instance */
struct z_kernel _kernel;

void z_time_slice(int ticks)
{
}

void z_ready_thread(struct k_thread *thread)
{
}

void z_move_thread_to_end_of_prio_q(struct k_thread *thread)
{
}

void z_sched_start(struct k_thread *thread)
{
}

void z_thread_single_abort(struct k_thread *thread)
{
}

ALWAYS_INLINE struct k_thread *z_find_first_thread_to_unpend(_wait_q_t *wait_q,
						     struct k_thread *from)
{
	return NULL;
}

ALWAYS_INLINE void z_unpend_thread_no_timeout(struct k_thread *thread)
{
}

void z_thread_timeout(struct _timeout *timeout)
{
}

int z_pend_curr(struct k_spinlock *lock, k_spinlock_key_t key,
	       _wait_q_t *wait_q, k_timeout_t timeout)
{
	return 0;
}

struct k_thread *z_unpend_first_thread(_wait_q_t *wait_q)
{
	return NULL;
}

void z_reschedule(struct k_spinlock *lock, k_spinlock_key_t key)
{
}

void z_reschedule_irqlock(u32_t key)
{
}

bool z_priq_rb_lessthan(struct rbnode *a, struct rbnode *b)
{
	return false;
}

void z_priq_rb_add(struct _priq_rb *pq, struct k_thread *thread)
{
}

void z_priq_rb_remove(struct _priq_rb *pq, struct k_thread *thread)
{
}

struct k_thread *z_priq_rb_best(struct _priq_rb *pq)
{
	return NULL;
}

void z_impl_k_yield(void)
{
}

s32_t z_impl_k_sleep(k_timeout_t timeout)
{
	return 0;
}

k_tid_t z_impl_k_current_get(void)
{
	return NULL;
}
