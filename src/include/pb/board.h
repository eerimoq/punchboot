/**
 * Punch BOOT
 *
 * Copyright (C) 2018 Jonas Persson <jonpe960@gmail.com>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdint.h>
#include <stdbool.h>
#include <pb.h>
#include <plat/defs.h>
#include <board/config.h>
#include <fuse.h>
#include <gpt.h>
#include <params.h>

/**
 * Function: board_early_init
 *
 * Called as early as possible by platform init code
 *
 * Return value: PB_OK if there is no error
 */
uint32_t board_early_init(struct pb_platform_setup *plat);

/**
 * Function: board_late_init
 *
 * Called as a last step in the platform init code
 *
 * Return value: PB_OK if there is no error
 */
uint32_t board_late_init(struct pb_platform_setup *plat);

/**
 * Function: board_prepare_recovery
 *
 * Called before recovery mode is to be initialized and before
 *  usb controller is initialized.
 *
 * Return value: PB_OK if there is no error
 */
uint32_t board_prepare_recovery(struct pb_platform_setup *plat);

/**
 * Function: board_force_recovery
 *
 * Called during initialization and forces recovery mode depending on return
 *   value.
 *
 * Return value: True - Force recovery
 *               False - Normal boot
 */
bool  board_force_recovery(struct pb_platform_setup *plat);

uint32_t board_setup_device(struct param *params);
uint32_t board_setup_lock(void);
uint32_t board_get_params(struct param **pp);
#endif
