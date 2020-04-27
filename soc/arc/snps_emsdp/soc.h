/*
 * Copyright (c) 2019 Synopsys, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @brief Board configuration macros for EM Software Development Platform board
 *
 * This header file is used to specify and describe board-level
 * aspects for the target.
 */

#ifndef _SOC_H_
#define _SOC_H_

#include <sys/util.h>

/* default system clock */
#define SYSCLK_DEFAULT_IOSC_HZ			MHZ(100)

/* ARC EM Core IRQs */
#define IRQ_TIMER0				16

#ifndef _ASMLANGUAGE

#include <sys/util.h>

#endif /* !_ASMLANGUAGE */

#endif /* _SOC_H_ */
