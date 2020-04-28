/*
 * Copyright (c) 2018-2019 Nordic Semiconductor ASA
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Public APIs for UART drivers
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_UART_H_
#define ZEPHYR_INCLUDE_DRIVERS_UART_H_

typedef void (*uart_irq_callback_user_data_t)(void *user_data);
typedef void (*uart_irq_callback_t)(struct device *port);

__syscall int uart_poll_in(struct device *dev, unsigned char *p_char);

static inline int z_impl_uart_poll_in(struct device *dev, unsigned char *p_char)
{
	return 0;
}


__syscall void uart_poll_out(struct device *dev,
				      unsigned char out_char);

static inline void z_impl_uart_poll_out(struct device *dev,
						unsigned char out_char)
{
}

#ifdef CONFIG_UART_INTERRUPT_DRIVEN


static inline int uart_fifo_fill(struct device *dev, const u8_t *tx_data,
				 int size)
{
	return 0;
}

static inline int uart_fifo_read(struct device *dev, u8_t *rx_data,
				 const int size)
{
	return 0;
}


__syscall void uart_irq_tx_enable(struct device *dev);

static inline void z_impl_uart_irq_tx_enable(struct device *dev)
{
	
}

__syscall void uart_irq_tx_disable(struct device *dev);

static inline void z_impl_uart_irq_tx_disable(struct device *dev)
{
}


static inline int uart_irq_tx_ready(struct device *dev)
{
	return 0;
}

__syscall void uart_irq_rx_enable(struct device *dev);

static inline void z_impl_uart_irq_rx_enable(struct device *dev)
{
}

__syscall void uart_irq_rx_disable(struct device *dev);

static inline void z_impl_uart_irq_rx_disable(struct device *dev)
{
}

static inline int uart_irq_rx_ready(struct device *dev)
{
	return 0;
}
__syscall int uart_irq_is_pending(struct device *dev);

__syscall int uart_irq_update(struct device *dev);

static inline void uart_irq_callback_user_data_set(
					struct device *dev,
					uart_irq_callback_user_data_t cb,
					void *user_data)
{
}

static inline void uart_irq_callback_set(struct device *dev,
					 uart_irq_callback_t cb)
{
}

#endif

/**
 * @}
 */

#include <syscalls/uart.h>

#endif /* ZEPHYR_INCLUDE_DRIVERS_UART_H_ */
