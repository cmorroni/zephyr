/* atomic operations */

/*
 * Copyright (c) 1997-2015, Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_SYS_ATOMIC_H_
#define ZEPHYR_INCLUDE_SYS_ATOMIC_H_

#include <stdbool.h>
#include <toolchain.h>
#include <stddef.h>

#include <zephyr/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int atomic_t;
typedef atomic_t atomic_val_t;
typedef void *atomic_ptr_t;

/**
 * @defgroup atomic_apis Atomic Services APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @brief Atomic compare-and-set.
 *
 * This routine performs an atomic compare-and-set on @a target. If the current
 * value of @a target equals @a old_value, @a target is set to @a new_value.
 * If the current value of @a target does not equal @a old_value, @a target
 * is left unchanged.
 *
 * @param target Address of atomic variable.
 * @param old_value Original value to compare against.
 * @param new_value New value to store.
 * @return true if @a new_value is written, false otherwise.
 */
static inline bool atomic_cas(atomic_t *target, atomic_val_t old_value,
			  atomic_val_t new_value)
{
	return 0;
}

/**
 *
 * @brief Atomic addition.
 *
 * This routine performs an atomic addition on @a target.
 *
 * @param target Address of atomic variable.
 * @param value Value to add.
 *
 * @return Previous value of @a target.
 */
static inline atomic_val_t atomic_add(atomic_t *target, atomic_val_t value)
{
	return 0;
}

/**
 *
 * @brief Atomic subtraction.
 *
 * This routine performs an atomic subtraction on @a target.
 *
 * @param target Address of atomic variable.
 * @param value Value to subtract.
 *
 * @return Previous value of @a target.
 */
static inline atomic_val_t atomic_sub(atomic_t *target, atomic_val_t value)
{
	return 0;
}

/**
 *
 * @brief Atomic increment.
 *
 * This routine performs an atomic increment by 1 on @a target.
 *
 * @param target Address of atomic variable.
 *
 * @return Previous value of @a target.
 */
static inline atomic_val_t atomic_inc(atomic_t *target)
{
	return 0;
}

/**
 *
 * @brief Atomic decrement.
 *
 * This routine performs an atomic decrement by 1 on @a target.
 *
 * @param target Address of atomic variable.
 *
 * @return Previous value of @a target.
 */
static inline atomic_val_t atomic_dec(atomic_t *target)
{
	return 0;
}

/**
 *
 * @brief Atomic get.
 *
 * This routine performs an atomic read on @a target.
 *
 * @param target Address of atomic variable.
 *
 * @return Value of @a target.
 */
static inline atomic_val_t atomic_get(const atomic_t *target)
{
	return 0;
}

/**
 *
 * @brief Atomic get-and-set.
 *
 * This routine atomically sets @a target to @a value and returns
 * the previous value of @a target.
 *
 * @param target Address of atomic variable.
 * @param value Value to write to @a target.
 *
 * @return Previous value of @a target.
 */
static inline atomic_val_t atomic_set(atomic_t *target, atomic_val_t value)
{
	/* This builtin, as described by Intel, is not a traditional
	 * test-and-set operation, but rather an atomic exchange operation. It
	 * writes value into *ptr, and returns the previous contents of *ptr.
	 */
	return 0;
}

/**
 *
 * @brief Atomic clear.
 *
 * This routine atomically sets @a target to zero and returns its previous
 * value. (Hence, it is equivalent to atomic_set(target, 0).)
 *
 * @param target Address of atomic variable.
 *
 * @return Previous value of @a target.
 */
static inline atomic_val_t atomic_clear(atomic_t *target)
{
	return 0;
}

/**
 *
 * @brief Atomic bitwise inclusive OR.
 *
 * This routine atomically sets @a target to the bitwise inclusive OR of
 * @a target and @a value.
 *
 * @param target Address of atomic variable.
 * @param value Value to OR.
 *
 * @return Previous value of @a target.
 */
static inline atomic_val_t atomic_or(atomic_t *target, atomic_val_t value)
{
	return 0;
}

/**
 *
 * @brief Atomic bitwise AND.
 *
 * This routine atomically sets @a target to the bitwise AND of @a target
 * and @a value.
 *
 * @param target Address of atomic variable.
 * @param value Value to AND.
 *
 * @return Previous value of @a target.
 */
static inline atomic_val_t atomic_and(atomic_t *target, atomic_val_t value)
{
	return 0;
}

/**
 * @cond INTERNAL_HIDDEN
 */

#define ATOMIC_BITS (sizeof(atomic_val_t) * 8)
#define ATOMIC_MASK(bit) (1 << ((u32_t)(bit) & (ATOMIC_BITS - 1)))
#define ATOMIC_ELEM(addr, bit) ((addr) + ((bit) / ATOMIC_BITS))

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @brief Define an array of atomic variables.
 *
 * This macro defines an array of atomic variables containing at least
 * @a num_bits bits.
 *
 * @note
 * If used from file scope, the bits of the array are initialized to zero;
 * if used from within a function, the bits are left uninitialized.
 *
 * @param name Name of array of atomic variables.
 * @param num_bits Number of bits needed.
 */
#define ATOMIC_DEFINE(name, num_bits) \
	atomic_t name[1 + ((num_bits) - 1) / ATOMIC_BITS]

/**
 * @brief Atomically test a bit.
 *
 * This routine tests whether bit number @a bit of @a target is set or not.
 * The target may be a single atomic variable or an array of them.
 *
 * @param target Address of atomic variable or array.
 * @param bit Bit number (starting from 0).
 *
 * @return true if the bit was set, false if it wasn't.
 */
static inline bool atomic_test_bit(const atomic_t *target, int bit)
{
	return false;
}

/**
 * @brief Atomically test and clear a bit.
 *
 * Atomically clear bit number @a bit of @a target and return its old value.
 * The target may be a single atomic variable or an array of them.
 *
 * @param target Address of atomic variable or array.
 * @param bit Bit number (starting from 0).
 *
 * @return true if the bit was set, false if it wasn't.
 */
static inline bool atomic_test_and_clear_bit(atomic_t *target, int bit)
{
	return false;
}

/**
 * @brief Atomically set a bit.
 *
 * Atomically set bit number @a bit of @a target and return its old value.
 * The target may be a single atomic variable or an array of them.
 *
 * @param target Address of atomic variable or array.
 * @param bit Bit number (starting from 0).
 *
 * @return true if the bit was set, false if it wasn't.
 */
static inline bool atomic_test_and_set_bit(atomic_t *target, int bit)
{
	return false;
}

/**
 * @brief Atomically clear a bit.
 *
 * Atomically clear bit number @a bit of @a target.
 * The target may be a single atomic variable or an array of them.
 *
 * @param target Address of atomic variable or array.
 * @param bit Bit number (starting from 0).
 *
 * @return N/A
 */
static inline void atomic_clear_bit(atomic_t *target, int bit)
{
}

/**
 * @brief Atomically set a bit.
 *
 * Atomically set bit number @a bit of @a target.
 * The target may be a single atomic variable or an array of them.
 *
 * @param target Address of atomic variable or array.
 * @param bit Bit number (starting from 0).
 *
 * @return N/A
 */
static inline void atomic_set_bit(atomic_t *target, int bit)
{
}

/**
 * @brief Atomically set a bit to a given value.
 *
 * Atomically set bit number @a bit of @a target to value @a val.
 * The target may be a single atomic variable or an array of them.
 *
 * @param target Address of atomic variable or array.
 * @param bit Bit number (starting from 0).
 * @param val true for 1, false for 0.
 *
 * @return N/A
 */
static inline void atomic_set_bit_to(atomic_t *target, int bit, bool val)
{
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_SYS_ATOMIC_H_ */
