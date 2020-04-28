/*
 * Copyright (c) 2017 Nordic Semiconductor ASA
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Public API for FLASH drivers
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_FLASH_H_
#define ZEPHYR_INCLUDE_DRIVERS_FLASH_H_

/**
 * @brief FLASH Interface
 * @defgroup flash_interface FLASH Interface
 * @ingroup io_interfaces
 * @{
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <sys/types.h>
#include <device.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CONFIG_FLASH_PAGE_LAYOUT)
struct flash_pages_layout {
	size_t pages_count; /* count of pages sequence of the same size */
	size_t pages_size;
};
#endif /* CONFIG_FLASH_PAGE_LAYOUT */

typedef int (*flash_api_read)(struct device *dev, off_t offset, void *data,
			      size_t len);
typedef int (*flash_api_write)(struct device *dev, off_t offset,
			       const void *data, size_t len);
typedef int (*flash_api_erase)(struct device *dev, off_t offset, size_t size);
typedef int (*flash_api_write_protection)(struct device *dev, bool enable);

#if defined(CONFIG_FLASH_PAGE_LAYOUT)
typedef void (*flash_api_pages_layout)(struct device *dev,
				       const struct flash_pages_layout **layout,
				       size_t *layout_size);
#endif /* CONFIG_FLASH_PAGE_LAYOUT */

__subsystem struct flash_driver_api {
	flash_api_read read;
	flash_api_write write;
	flash_api_erase erase;
	flash_api_write_protection write_protection;
#if defined(CONFIG_FLASH_PAGE_LAYOUT)
	flash_api_pages_layout page_layout;
#endif /* CONFIG_FLASH_PAGE_LAYOUT */
	const size_t write_block_size;
};

__syscall int flash_read(struct device *dev, off_t offset, void *data,
			 size_t len);

static inline int z_impl_flash_read(struct device *dev, off_t offset, void *data,
			     size_t len)
{
	*(int *)data = 0;
	return 0;
}

__syscall int flash_write(struct device *dev, off_t offset, const void *data,
			  size_t len);

static inline int z_impl_flash_write(struct device *dev, off_t offset,
				    const void *data, size_t len)
{
	return 0;
}

__syscall int flash_erase(struct device *dev, off_t offset, size_t size);

static inline int z_impl_flash_erase(struct device *dev, off_t offset,
				    size_t size)
{
	return 0;
}

__syscall int flash_write_protection_set(struct device *dev, bool enable);

static inline int z_impl_flash_write_protection_set(struct device *dev,
						   bool enable)
{
	return 0;
}

struct flash_pages_info {
	off_t start_offset; /* offset from the base of flash address */
	size_t size;
	u32_t index;
};

__syscall int flash_get_page_info_by_offs(struct device *dev, off_t offset, struct flash_pages_info *info);
__syscall size_t flash_get_write_block_size(struct device *dev);

static inline size_t z_impl_flash_get_write_block_size(struct device *dev)
{
	return 0;
}

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#include <syscalls/flash.h>

#endif /* ZEPHYR_INCLUDE_DRIVERS_FLASH_H_ */
