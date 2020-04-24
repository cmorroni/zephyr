/*
 * Copyright (c) 2019 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>

#include <logging/log.h>

LOG_MODULE_DECLARE(os);

static inline int get_cpu(void)
{
	return 0;
}

void z_fatal_error(unsigned int reason, const z_arch_esf_t *esf)
{
}
