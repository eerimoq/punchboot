
/**
 * Punch BOOT
 *
 * Copyright (C) 2018 Jonas Persson <jonpe960@gmail.com>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __PB_CONFIG_H__
#define __PB_CONFIG_H__

#include <stdint.h>
#include <stdbool.h>

#define PB_CONFIG_MAGIC 0x026d4a65

#define PB_CONFIG_A_ENABLED (1 << 0)
#define PB_CONFIG_B_ENABLED (1 << 1)
#define PB_CONFIG_A_VERIFIED (1 << 0)
#define PB_CONFIG_B_VERIFIED (1 << 1)
#define PB_CONFIG_ERROR_A_ROLLBACK (1 << 0)
#define PB_CONFIG_ERROR_B_ROLLBACK (1 << 1)

struct config
{
    uint32_t magic;
    uint32_t enable;
    uint32_t verified;
    uint32_t remaining_boot_attempts;
    uint32_t error;
    uint8_t rz[488];
    uint32_t crc;
} __attribute__ ((packed));

#ifdef __PB_BUILD

uint32_t config_init(void);
uint32_t config_commit(void);
bool config_system_enabled(uint32_t system);
void config_system_enable(uint32_t system);
bool config_system_verified(uint32_t system);
void config_system_set_verified(uint32_t system, bool verified);
uint32_t config_get_remaining_boot_attempts(void);
void config_decrement_boot_attempt(void);
void config_set_boot_error(uint32_t bits);
#endif

#endif
