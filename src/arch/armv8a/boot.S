/**
 * Punch BOOT
 *
 * Copyright (C) 2018 Jonas Persson <jonpe960@gmail.com>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <arch/armv8a/include/arch/arch.h>
#include <arch/armv8a/asm_macros.S>

.section .text

.global arch_jump_linux_dt

arch_jump_linux_dt:
    b .

.global arch_jump_atf
arch_jump_atf:

    mov x4, x0 /* Jump address */
    mov x5, x1 /* Device tree address */

    mov x0, x5
    ldr x1, =0
    ldr x2, =0
    ldr x3, =0


    ic ivau, x4
    isb sy
    dsb sy

    br x4
    b .


.global arch_jump
arch_jump:
    mov x4, x0 /* Jump address */
    mov x5, x1 /* Arg1 */
    mov x6, x2 /* Arg2 */
    mov x7, x3 /* Arg3 */

    mov x0, x5
    mov x1, x6
    mov x2, x7
    ldr x3, =0

    ic ivau, x4
    isb sy
    dsb sy

    br x4
    b .
