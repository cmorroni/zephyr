/*
 * Copyright (c) 2015 Intel corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Public interface for configuring interrupts
 */
#ifndef ZEPHYR_INCLUDE_IRQ_H_
#define ZEPHYR_INCLUDE_IRQ_H_

#ifndef _ASMLANGUAGE

#ifdef __cplusplus
extern "C" {
#endif

#define irq_lock() false
#define irq_unlock(key) false

#ifdef __cplusplus
}
#endif

#endif /* ASMLANGUAGE */
#endif /* ZEPHYR_INCLUDE_IRQ_H_ */
