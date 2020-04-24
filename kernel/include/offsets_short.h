/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_KERNEL_INCLUDE_OFFSETS_SHORT_H_
#define ZEPHYR_KERNEL_INCLUDE_OFFSETS_SHORT_H_

#include <offsets_short_arch.h>

/* kernel */

#define _kernel_offset_to_nested \
	(___kernel_t_nested_OFFSET)

#define _kernel_offset_to_irq_stack \
	(___kernel_t_irq_stack_OFFSET)

#define _kernel_offset_to_current \
	(___kernel_t_current_OFFSET)

#define _kernel_offset_to_ready_q_cache \
	(___kernel_t_ready_q_OFFSET + ___ready_q_t_cache_OFFSET)

/* end - kernel */


#endif /* ZEPHYR_KERNEL_INCLUDE_OFFSETS_SHORT_H_ */
