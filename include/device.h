/*
 * Copyright (c) 2015 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DEVICE_H_
#define ZEPHYR_INCLUDE_DEVICE_H_

#include <kernel.h>

/**
 * @brief Device Driver APIs
 * @defgroup io_interfaces Device Driver APIs
 * @{
 * @}
 */
/**
 * @brief Device Model APIs
 * @defgroup device_model Device Model APIs
 * @{
 */

#include <zephyr/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def DEVICE_AND_API_INIT
 *
 * @brief Create device object and set it up for boot time initialization,
 * with the option to set driver_api.
 *
 * @copydetails DEVICE_INIT
 * @param api Provides an initial pointer to the API function struct
 * used by the driver. Can be NULL.
 * @details The driver api is also set here, eliminating the need to do that
 * during initialization.
 */
#define DEVICE_AND_API_INIT(dev_name, drv_name, init_fn, data, cfg_info,  \
			    level, prio, api)				  \
	static const struct device_config _CONCAT(__config_, dev_name) __used \
	__attribute__((__section__(".devconfig.init"))) = {		  \
		.name = drv_name, .init = (init_fn),			  \
		.config_info = (cfg_info)				  \
	};								  \
	static Z_DECL_ALIGN(struct device) _CONCAT(__device_, dev_name) __used \
	__attribute__((__section__(".init_" #level STRINGIFY(prio)))) = { \
		.config = &_CONCAT(__config_, dev_name),		  \
		.driver_api = api,					  \
		.driver_data = data					  \
	}

struct device;

/**
 * @brief Static device information (In ROM) Per driver instance
 *
 * @param name name of the device
 * @param init init function for the driver
 * @param config_info address of driver instance config information
 */
struct device_config {
	const char *name;
	int (*init)(struct device *device);
#ifdef CONFIG_DEVICE_POWER_MANAGEMENT
	int (*device_pm_control)(struct device *device, u32_t command,
				 void *context, device_pm_cb cb, void *arg);
	struct device_pm *pm;
#endif
	const void *config_info;
};

/**
 * @brief Runtime device structure (In memory) Per driver instance
 * @param device_config Build time config information
 * @param driver_api pointer to structure containing the API functions for
 * the device type. This pointer is filled in by the driver at init time.
 * @param driver_data driver instance data. For driver use only
 */
struct device {
	const struct device_config *config;
	const void *driver_api;
	void *driver_data;
};

/**
 * @brief Retrieve the device structure for a driver by name
 *
 * @details Device objects are created via the DEVICE_INIT() macro and
 * placed in memory by the linker. If a driver needs to bind to another driver
 * it can use this function to retrieve the device structure of the lower level
 * driver by the name the driver exposes to the system.
 *
 * @param name device name to search for.
 *
 * @return pointer to device structure; NULL if not found or cannot be used.
 */
__syscall struct device *device_get_binding(const char *name);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#include <syscalls/device.h>

#endif /* ZEPHYR_INCLUDE_DEVICE_H_ */
