/*
 * Copyright (c) 2015 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_INIT_H_
#define ZEPHYR_INCLUDE_INIT_H_

#include <device.h>

#ifdef __cplusplus
extern "C" {
#endif

/* A counter is used to avoid issues when two or more system devices
 * are declared in the same C file with the same init function.
 */
#define Z_SYS_NAME(init_fn) _CONCAT(_CONCAT(sys_init_, init_fn), __COUNTER__)

/**
 * @def SYS_INIT
 *
 * @brief Run an initialization function at boot at specified priority
 *
 * @details This macro lets you run a function at system boot.
 *
 * @param init_fn Pointer to the boot function to run
 *
 * @param level The initialization level, See DEVICE_AND_API_INIT for details.
 *
 * @param prio Priority within the selected initialization level. See
 * DEVICE_AND_API_INIT for details.
 */
#define SYS_INIT(init_fn, level, prio) \
	DEVICE_AND_API_INIT(Z_SYS_NAME(init_fn), "", init_fn, NULL, NULL, level,\
	prio, NULL)

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_INIT_H_ */
