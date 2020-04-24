/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Message queues.
 */


#include <kernel.h>

int z_impl_k_msgq_put(struct k_msgq *msgq, void *data, k_timeout_t timeout)
{
	return 0;
}

int z_impl_k_msgq_get(struct k_msgq *msgq, void *data, k_timeout_t timeout)
{
	return 0;
}

int z_impl_k_msgq_peek(struct k_msgq *msgq, void *data)
{
	return 0;
}
