/*  NVS: non volatile storage in flash
 *
 * Copyright (c) 2018 Laczen
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_INCLUDE_FS_NVS_H_
#define ZEPHYR_INCLUDE_FS_NVS_H_

#include <sys/types.h>
#include <kernel.h>
#include <device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Non-volatile Storage
 * @defgroup nvs Non-volatile Storage
 * @ingroup file_system_storage
 * @{
 * @}
 */

/**
 * @brief Non-volatile Storage Data Structures
 * @defgroup nvs_data_structures Non-volatile Storage Data Structures
 * @ingroup nvs
 * @{
 */

/**
 * @brief Non-volatile Storage File system structure
 *
 * @param offset File system offset in flash
 * @param ate_wra: Allocation table entry write address. Addresses are stored
 * as u32_t: high 2 bytes are sector, low 2 bytes are offset in sector,
 * @param data_wra: Data write address.
 * @param sector_size File system is divided into sectors each sector should be
 * multiple of pagesize
 * @param sector_count Amount of sectors in the file systems
 * @param write_block_size Alignment size
 * @param nvs_lock Mutex
 * @param flash_device Flash Device
 */
struct nvs_fs {
	off_t offset;		/* filesystem offset in flash */
	u32_t ate_wra;		/* next alloc table entry write address */
	u32_t data_wra;		/* next data write address */
	u16_t sector_size;	/* filesystem is divided into sectors,
				 * sector size should be multiple of pagesize
				 */
	u16_t sector_count;	/* amount of sectors in the filesystem */
	u8_t write_block_size;  /* write block size for alignment */
	bool ready;		/* is the filesystem initialized ? */

	struct k_mutex nvs_lock;
	struct device *flash_device;
};

/**
 * @}
 */

/**
 * @brief Non-volatile Storage APIs
 * @defgroup nvs_high_level_api Non-volatile Storage APIs
 * @ingroup nvs
 * @{
 */

int nvs_init(struct nvs_fs *fs, const char *dev_name);
ssize_t nvs_write(struct nvs_fs *fs, u16_t id, const void *data, size_t len);
int nvs_delete(struct nvs_fs *fs, u16_t id);
ssize_t nvs_read(struct nvs_fs *fs, u16_t id, void *data, size_t len);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_FS_NVS_H_ */
