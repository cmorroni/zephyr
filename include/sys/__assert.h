/*
 * Copyright (c) 2011-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_SYS___ASSERT_H_
#define ZEPHYR_INCLUDE_SYS___ASSERT_H_

#if defined(CONFIG_ASSERT_VERBOSE)
#define __ASSERT_PRINT(fmt, ...) printk(fmt, ##__VA_ARGS__)
#else /* CONFIG_ASSERT_VERBOSE */
#define __ASSERT_PRINT(fmt, ...)
#endif /* CONFIG_ASSERT_VERBOSE */

#ifdef CONFIG_ASSERT_NO_MSG_INFO
#define __ASSERT_MSG_INFO(fmt, ...)
#else  /* CONFIG_ASSERT_NO_MSG_INFO */
#define __ASSERT_MSG_INFO(fmt, ...) __ASSERT_PRINT("\t" fmt "\n", ##__VA_ARGS__)
#endif /* CONFIG_ASSERT_NO_MSG_INFO */

#if !defined(CONFIG_ASSERT_NO_COND_INFO) && !defined(CONFIG_ASSERT_NO_FILE_INFO)
#define __ASSERT_LOC(test)                              \
	__ASSERT_PRINT("ASSERTION FAIL [%s] @ %s:%d\n", \
		Z_STRINGIFY(test),                      \
		__FILE__, __LINE__)
#endif

#define __ASSERT(test, fmt, ...) { }
#define __ASSERT_NO_MSG(test) { }

#endif /* ZEPHYR_INCLUDE_SYS___ASSERT_H_ */
