/*
 * Copyright (c) 1984-2008, 2011-2015 Wind River Systems, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * driver for x86 CPU local APIC (as an interrupt controller)
 */

#include <kernel.h>

/**
 * @brief Enable and initialize the local APIC.
 *
 * Called from early assembly layer (e.g., crt0.S).
 */

void z_loapic_enable(void)
{
}


/**
 * @brief Find the currently executing interrupt vector, if any
 *
 * This routine finds the vector of the interrupt that is being processed.
 * The ISR (In-Service Register) register contain the vectors of the interrupts
 * in service. And the higher vector is the identification of the interrupt
 * being currently processed.
 *
 * This function must be called with interrupts locked in interrupt context.
 *
 * ISR registers' offsets:
 * --------------------
 * | Offset | bits    |
 * --------------------
 * | 0100H  |   0:31  |
 * | 0110H  |  32:63  |
 * | 0120H  |  64:95  |
 * | 0130H  |  96:127 |
 * | 0140H  | 128:159 |
 * | 0150H  | 160:191 |
 * | 0160H  | 192:223 |
 * | 0170H  | 224:255 |
 * --------------------
 *
 * @return The vector of the interrupt that is currently being processed, or -1
 * if no IRQ is being serviced.
 */
int z_irq_controller_isr_vector_get(void)
{
	return 0;
}

