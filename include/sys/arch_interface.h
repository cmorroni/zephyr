/*
 * Copyright (c) 2019 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @defgroup arch-interface Architecture Interface
 * @brief Internal kernel APIs with public scope
 *
 * Any public kernel APIs that are implemented as inline functions and need to
 * call architecture-specific API so will have the prototypes for the
 * architecture-specific APIs here. Architecture APIs that aren't used in this
 * way go in kernel/include/kernel_arch_interface.h.
 *
 * The set of architecture-specific APIs used internally by public macros and
 * inline functions in public headers are also specified and documented.
 *
 * For all macros and inline function prototypes described herein, <arch/cpu.h>
 * must eventually pull in full definitions for all of them (the actual macro
 * defines and inline function bodies)
 *
 * include/kernel.h and other public headers depend on definitions in this
 * header.
 */
#ifndef ZEPHYR_INCLUDE_SYS_ARCH_INTERFACE_H_
#define ZEPHYR_INCLUDE_SYS_ARCH_INTERFACE_H_

#ifndef _ASMLANGUAGE

#ifdef __cplusplus
extern "C" {
#endif

typedef struct z_thread_stack_element k_thread_stack_t;

typedef void (*k_thread_entry_t)(void *p1, void *p2, void *p3);

/**
 * @addtogroup arch-pm
 * @{
 */

/**
 * @brief Power save idle routine
 *
 * This function will be called by the kernel idle loop or possibly within
 * an implementation of z_sys_power_save_idle in the kernel when the
 * '_sys_power_save_flag' variable is non-zero.
 *
 * Architectures that do not implement power management instructions may
 * immediately return, otherwise a power-saving instruction should be
 * issued to wait for an interrupt.
 *
 * @note The function is expected to return after the interrupt that has
 * caused the CPU to exit power-saving mode has been serviced, although
 * this is not a firm requirement.
 *
 * @see k_cpu_idle()
 */
void arch_cpu_idle(void);

/**
 * @brief Atomically re-enable interrupts and enter low power mode
 *
 * The requirements for arch_cpu_atomic_idle() are as follows:
 *
 * -# Enabling interrupts and entering a low-power mode needs to be
 *    atomic, i.e. there should be no period of time where interrupts are
 *    enabled before the processor enters a low-power mode.  See the comments
 *    in k_lifo_get(), for example, of the race condition that
 *    occurs if this requirement is not met.
 *
 * -# After waking up from the low-power mode, the interrupt lockout state
 *    must be restored as indicated in the 'key' input parameter.
 *
 * @see k_cpu_atomic_idle()
 *
 * @param key Lockout key returned by previous invocation of arch_irq_lock()
 */
void arch_cpu_atomic_idle(unsigned int key);

/** @} */


/**
 * @addtogroup arch-irq
 * @{
 */

/**
 * Arch-specific hook to install a dynamic interrupt.
 *
 * @param irq IRQ line number
 * @param priority Interrupt priority
 * @param routine Interrupt service routine
 * @param parameter ISR parameter
 * @param flags Arch-specific IRQ configuration flag
 *
 * @return The vector assigned to this interrupt
 */
int arch_irq_connect_dynamic(unsigned int irq, unsigned int priority,
			     void (*routine)(void *parameter),
			     void *parameter, u32_t flags);

/** @} */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ASMLANGUAGE */

#endif /* ZEPHYR_INCLUDE_SYS_ARCH_INTERFACE_H_ */
