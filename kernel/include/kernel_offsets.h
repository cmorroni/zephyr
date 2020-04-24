/*
 * Copyright (c) 2013-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <device.h>

#ifndef ZEPHYR_KERNEL_INCLUDE_KERNEL_OFFSETS_H_
#define ZEPHYR_KERNEL_INCLUDE_KERNEL_OFFSETS_H_

GEN_ABS_SYM_BEGIN(_OffsetAbsSyms)

GEN_OFFSET_SYM(_kernel_t, current);
GEN_OFFSET_SYM(_kernel_t, nested);
GEN_OFFSET_SYM(_kernel_t, irq_stack);

GEN_OFFSET_SYM(_kernel_t, ready_q);

GEN_OFFSET_SYM(_ready_q_t, cache);

GEN_OFFSET_SYM(_thread_t, callee_saved);

/* LCOV_EXCL_STOP */
#endif /* ZEPHYR_KERNEL_INCLUDE_KERNEL_OFFSETS_H_ */
