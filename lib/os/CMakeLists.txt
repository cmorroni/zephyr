# SPDX-License-Identifier: Apache-2.0

zephyr_sources(
  crc8_sw.c
  dec.c
  hex.c
  printk.c
  )

zephyr_sources_if_kconfig(ring_buffer.c)
