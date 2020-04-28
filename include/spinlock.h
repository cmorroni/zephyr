/*
 * Copyright (c) 2018 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_INCLUDE_SPINLOCK_H_
#define ZEPHYR_INCLUDE_SPINLOCK_H_

#include <sys/atomic.h>
#include <kernel_structs.h>

/* There's a spinlock validation framework available when asserts are
 * enabled.  It adds a relatively hefty overhead (about 3k or so) to
 * kernel code size, don't use on platforms known to be small.
 */
#ifdef CONFIG_SPIN_VALIDATE
#include <sys/__assert.h>
#include <stdbool.h>
struct k_spinlock;
bool z_spin_lock_valid(struct k_spinlock *l);
bool z_spin_unlock_valid(struct k_spinlock *l);
void z_spin_lock_set_owner(struct k_spinlock *l);
BUILD_ASSERT(CONFIG_MP_NUM_CPUS < 4, "Too many CPUs for mask");
#endif /* CONFIG_SPIN_VALIDATE */

struct k_spinlock_key {
	int key;
};

typedef struct k_spinlock_key k_spinlock_key_t;

static ALWAYS_INLINE k_spinlock_key_t k_spin_lock(struct k_spinlock *l)
{
	k_spinlock_key_t ret;
	ret.key = 0;
	return ret;
}

static ALWAYS_INLINE void k_spin_unlock(struct k_spinlock *l,
					k_spinlock_key_t key)
{
}


#endif /* ZEPHYR_INCLUDE_SPINLOCK_H_ */
