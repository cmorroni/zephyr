/*
 * Copyright (c) 2010-2012, 2014-2015 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Architecture-independent private kernel APIs
 *
 * This file contains private kernel APIs that are not architecture-specific.
 */

#ifndef ZEPHYR_KERNEL_INCLUDE_KERNEL_INTERNAL_H_
#define ZEPHYR_KERNEL_INCLUDE_KERNEL_INTERNAL_H_

#include <kernel.h>
#include <kernel_arch_interface.h>
#include <string.h>

#ifndef _ASMLANGUAGE

#ifdef __cplusplus
extern "C" {
#endif

extern FUNC_NORETURN void z_thread_entry(k_thread_entry_t entry,
			  void *p1, void *p2, void *p3);

static inline void z_new_thread_init(struct k_thread *thread,
				     char *stack, size_t stack_size)
{
}

#ifdef CONFIG_MULTITHREADING
extern struct k_thread z_idle_threads[CONFIG_MP_NUM_CPUS];
#endif
extern K_THREAD_STACK_ARRAY_DEFINE(z_interrupt_stacks, CONFIG_MP_NUM_CPUS,
				   CONFIG_ISR_STACK_SIZE);

#ifdef __cplusplus
}
#endif

#endif /* _ASMLANGUAGE */

#endif /* ZEPHYR_KERNEL_INCLUDE_KERNEL_INTERNAL_H_ */
