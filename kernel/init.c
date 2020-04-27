/*
 * Copyright (c) 2010-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(os);

/*
 * storage space for the interrupt stack
 *
 * Note: This area is used as the system stack during kernel initialization,
 * since the kernel hasn't yet set up its own stack areas. The dual purposing
 * of this area is safe since interrupts are disabled until the kernel context
 * switches to the init thread.
 */
K_THREAD_STACK_ARRAY_DEFINE(z_interrupt_stacks, CONFIG_MP_NUM_CPUS,
			    CONFIG_ISR_STACK_SIZE);

/**
 *
 * @brief Initialize kernel
 *
 * This routine is invoked when the system is ready to run C code. The
 * processor must be running in 32-bit mode, and the BSS must have been
 * cleared/zeroed.
 *
 * @return Does not return
 */
FUNC_NORETURN void z_cstart(void)
{
	while(1);
}
