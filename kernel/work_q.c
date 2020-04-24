/*
 * Copyright (c) 2016 Intel Corporation
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 *
 * Workqueue support functions
 */

#include <wait_q.h>

void k_delayed_work_init(struct k_delayed_work *work, k_work_handler_t handler)
{
}

int k_delayed_work_submit_to_queue(struct k_work_q *work_q,
				   struct k_delayed_work *work,
				   k_timeout_t delay)
{
	return 0;
}

int k_delayed_work_cancel(struct k_delayed_work *work)
{
	return 0;
}
