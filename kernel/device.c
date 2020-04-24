/*
 * Copyright (c) 2015-2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <device.h>

/**
 * @brief Execute all the device initialization functions at a given level
 *
 * @details Invokes the initialization routine for each device object
 * created by the DEVICE_INIT() macro using the specified level.
 * The linker script places the device objects in memory in the order
 * they need to be invoked, with symbols indicating where one level leaves
 * off and the next one begins.
 *
 * @param level init level to run.
 */
void z_sys_device_do_config_level(s32_t level)
{
}

struct device *z_impl_device_get_binding(const char *name)
{
	return NULL;
}
