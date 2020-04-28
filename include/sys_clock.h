/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Variables needed needed for system clock
 *
 *
 * Declare variables used by both system timer device driver and kernel
 * components that use timer functionality.
 */

#ifndef ZEPHYR_INCLUDE_SYS_CLOCK_H_
#define ZEPHYR_INCLUDE_SYS_CLOCK_H_

#include <sys/util.h>
#include <sys/dlist.h>

#include <toolchain.h>
#include <zephyr/types.h>

#include <sys/time_units.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup clock_apis
 * @{
 */

/**
 * @brief Tick precision used in timeout APIs
 *
 * This type defines the word size of the timeout values used in
 * k_timeout_t objects, and thus defines an upper bound on maximum
 * timeout length (or equivalently minimum tick duration).  Note that
 * this does not affect the size of the system uptime counter, which
 * is always a 64 bit count of ticks.
 */
#ifdef CONFIG_TIMEOUT_64BIT
typedef s64_t k_ticks_t;
#else
typedef u32_t k_ticks_t;
#endif

/* Legacy timeout API */
typedef s32_t k_timeout_t;
#define K_TIMEOUT_EQ(a, b) 0
#define Z_TIMEOUT_NO_WAIT 0
#define Z_TIMEOUT_TICKS(t) 0
#define Z_FOREVER 0
#define Z_TIMEOUT_MS(t) 0
#define Z_TIMEOUT_US(t) 0
#define Z_TIMEOUT_NS(t) 0
#define Z_TIMEOUT_CYC(t) 0

/** @} */

/* number of nsec per usec */
#define NSEC_PER_USEC 1000U

/* number of microseconds per millisecond */
#define USEC_PER_MSEC 1000U

/* number of milliseconds per second */
#define MSEC_PER_SEC 1000U

/* number of microseconds per second */
#define USEC_PER_SEC ((USEC_PER_MSEC) * (MSEC_PER_SEC))

/* number of nanoseconds per second */
#define NSEC_PER_SEC ((NSEC_PER_USEC) * (USEC_PER_MSEC) * (MSEC_PER_SEC))

s64_t z_tick_get(void);
u64_t z_timeout_end_calc(k_timeout_t timeout);

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_SYS_CLOCK_H_ */
