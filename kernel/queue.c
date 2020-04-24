/*
 * Copyright (c) 2010-2016 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 *
 * @brief dynamic-size QUEUE object.
 */


#include <kernel.h>

void *z_queue_node_peek(sys_sfnode_t *node, bool needs_free)
{
	return NULL;
}

void z_impl_k_queue_init(struct k_queue *queue)
{
}

void k_queue_append(struct k_queue *queue, void *data)
{
}

void k_queue_prepend(struct k_queue *queue, void *data)
{
}

int k_queue_append_list(struct k_queue *queue, void *head, void *tail)
{
	return 0;
}

void *z_impl_k_queue_get(struct k_queue *queue, k_timeout_t timeout)
{
	return NULL;
}
