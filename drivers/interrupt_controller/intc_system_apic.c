/*
 * Copyright (c) 2013-2015, Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief  system module for variants with LOAPIC
 *
 */

#include <kernel.h>

/**
 *
 * @brief Program interrupt controller
 *
 * This routine programs the interrupt controller with the given vector
 * based on the given IRQ parameter.
 *
 * Drivers call this routine instead of IRQ_CONNECT() when interrupts are
 * configured statically.
 *
 * The Galileo board virtualizes IRQs as follows:
 *
 * - The first CONFIG_IOAPIC_NUM_RTES IRQs are provided by the IOAPIC so the
 *     IOAPIC is programmed for these IRQs
 * - The remaining IRQs are provided by the LOAPIC and hence the LOAPIC is
 *     programmed.
 *
 * @param vector the vector number
 * @param irq the virtualized IRQ
 * @param flags interrupt flags
 *
 */
void z_irq_controller_irq_config(unsigned int vector, unsigned int irq,
				 u32_t flags)
{
}

/**
 *
 * @brief Enable an individual interrupt (IRQ)
 *
 * The public interface for enabling/disabling a specific IRQ for the IA-32
 * architecture is defined as follows in include/arch/x86/arch.h
 *
 *   extern void  irq_enable  (unsigned int irq);
 *   extern void  irq_disable (unsigned int irq);
 *
 * The irq_enable() routine is provided by the interrupt controller driver due
 * to the IRQ virtualization that is performed by this platform.  See the
 * comments in _interrupt_vector_allocate() for more information regarding IRQ
 * virtualization.
 *
 * @return N/A
 */
void arch_irq_enable(unsigned int irq)
{
}
