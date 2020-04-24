/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_KERNEL_INCLUDE_KSWAP_H_
#define ZEPHYR_KERNEL_INCLUDE_KSWAP_H_

static inline int z_swap_irqlock(unsigned int key)
{
	return 0;
}

#endif /* ZEPHYR_KERNEL_INCLUDE_KSWAP_H_ */
