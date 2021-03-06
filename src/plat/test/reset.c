
/**
 * Punch BOOT
 *
 * Copyright (C) 2018 Jonas Persson <jonpe960@gmail.com>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdio.h>
#include <pb.h>
#include <plat.h>
#include "pl061.h"
#include "gcov.h"
#include <plat/test/semihosting.h>

void plat_reset(void)
{
    gcov_final();
    semihosting_sys_exit(0);
}

