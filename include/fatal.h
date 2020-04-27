/*
 * Copyright (c) 2019 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/** @file
 *  @brief Fatal error functions
 */

#ifndef ZEPHYR_INCLUDE_FATAL_H
#define ZEPHYR_INCLUDE_FATAL_H

/**
 * @defgroup fatal_apis Fatal error APIs
 * @ingroup kernel_apis
 * @{
 */

enum k_fatal_error_reason {
	/** Generic CPU exception, not covered by other codes */
	K_ERR_CPU_EXCEPTION,

	/** Unhandled hardware interrupt */
	K_ERR_SPURIOUS_IRQ,

	/** Faulting context overflowed its stack buffer */
	K_ERR_STACK_CHK_FAIL,

	/** Moderate severity software error */
	K_ERR_KERNEL_OOPS,

	/** High severity software error */
	K_ERR_KERNEL_PANIC

	/* TODO: add more codes for exception types that are common across
	 * architectures
	 */
};

/**
 * Called by architecture code upon a fatal error.
 *
 * This function dumps out architecture-agnostic information about the error
 * and then makes a policy decision on what to do by invoking
 * k_sys_fatal_error_handler().
 *
 * On architectures where k_thread_abort() never returns, this function
 * never returns either.
 *
 * @param reason The reason for the fatal error
 * @param esf Exception context, with details and partial or full register
 *            state when the error occurred. May in some cases be NULL.
 */
void z_fatal_error(unsigned int reason, const z_arch_esf_t *esf);

/** @} */

#endif /* ZEPHYR_INCLUDE_FATAL_H */
