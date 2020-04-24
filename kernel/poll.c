/*
 * Copyright (c) 2017 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 *
 * @brief Kernel asynchronous event polling interface.
 *
 * This polling mechanism allows waiting on multiple events concurrently,
 * either events triggered directly, or from kernel objects or other kernel
 * constructs.
 */

#include <kernel.h>

void k_poll_event_init(struct k_poll_event *event, u32_t type,
		       int mode, void *obj)
{
}

int z_impl_k_poll(struct k_poll_event *events, int num_events,
		  k_timeout_t timeout)
{
	return 0;
}

void z_handle_obj_poll_events(sys_dlist_t *events, u32_t state)
{
}

void z_impl_k_poll_signal_init(struct k_poll_signal *signal)
{
}

void z_impl_k_poll_signal_check(struct k_poll_signal *signal,
			       unsigned int *signaled, int *result)
{
}

int z_impl_k_poll_signal_raise(struct k_poll_signal *signal, int result)
{
	return 0;
}
