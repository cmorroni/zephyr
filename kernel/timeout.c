/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>

int z_clock_hw_cycles_per_sec = CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC;

k_ticks_t z_timeout_remaining(struct _timeout *timeout)
{
	return 0;
}

s64_t z_tick_get(void)
{
	return 0;
}

s64_t z_impl_k_uptime_ticks(void)
{
	return 0;
}

/* Returns the uptime expiration (relative to an unlocked "now"!) of a
 * timeout object.  When used correctly, this should be called once,
 * synchronously with the user passing a new timeout value.  It should
 * not be used iteratively to adjust a timeout.
 */
u64_t z_timeout_end_calc(k_timeout_t timeout)
{
	return 0;
}
