/**
 * Punch BOOT bootloader cli
 *
 * Copyright (C) 2018 Jonas Persson <jonpe960@gmail.com>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdint.h>
#include <pb/gpt.h>

void utils_gpt_part_name(struct gpt_part_hdr *part, uint8_t *out, uint8_t len);
 

#endif
