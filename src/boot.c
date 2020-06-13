/**
 * Punch BOOT
 *
 * Copyright (C) 2018 Jonas Blixt <jonpe960@gmail.com>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdio.h>
#include <pb.h>
#include <io.h>
#include <boot.h>
#include <gpt.h>
#include <image.h>
#include <board/config.h>
#include <crypto.h>
#include <board.h>
#include <plat.h>
#include <atf.h>
#include <timing_report.h>
#include <libfdt.h>
#include <uuid.h>
#include <bpak/bpak.h>

extern void arch_jump_linux_dt(volatile void* addr, volatile void * dt)
                                 __attribute__((noreturn));

extern void arch_jump_atf(void* atf_addr, void * atf_param)
                                 __attribute__((noreturn));

extern uint32_t board_linux_patch_dt(void *fdt, int offset);

void pb_boot(struct bpak_header *h, uint32_t system_index, bool verbose)
{
    int rc = BPAK_OK;
    uint32_t *dtb = NULL;
    uint32_t *linux = NULL;
    uint32_t *atf = NULL;
    uint32_t *tee = NULL;
    uint32_t *ramdisk = NULL;

    tr_stamp_begin(TR_DT_PATCH);

    rc = bpak_valid_header(h);

    if (rc != BPAK_OK)
    {
        LOG_ERR("Invalid BPAK header");
        return;
    }

    bpak_foreach_part(h, p)
    {
        if (!p->id)
            break;

        if (p->id == 0xec103b08) /* kernel */
        {
            rc = bpak_get_meta_with_ref(h, 0xd1e64a4b, p->id, (void **) &linux);
            if (rc != BPAK_OK)
                break;
        }
        else if (p->id == 0x56f91b86) /* dt */
        {
            rc = bpak_get_meta_with_ref(h, 0xd1e64a4b, p->id, (void **) &dtb);

            if (rc != BPAK_OK)
                break;
        }
        else if (p->id == 0xf4cdac1f) /* ramdisk */
        {
            rc = bpak_get_meta_with_ref(h, 0xd1e64a4b, p->id, (void **) &ramdisk);

            if (rc != BPAK_OK)
                break;
        }
        else if (p->id == 0x76aacab9) /* tee */
        {
            rc = bpak_get_meta_with_ref(h, 0xd1e64a4b, p->id, (void **) &tee);

            if (rc != BPAK_OK)
                break;
        }
        else if (p->id == 0xa697d988) /* atf */
        {
            rc = bpak_get_meta_with_ref(h, 0xd1e64a4b, p->id, (void **) &atf);

            if (rc != BPAK_OK)
                break;
        }

        if (rc != BPAK_OK)
        {
            LOG_ERR("Could get entry for %x", p->id);
            return;
        }
    }

    if (dtb)
        LOG_INFO("DTB 0x%x", *dtb);
    else
        LOG_INFO("No DTB");

    if (linux)
        LOG_INFO("LINUX 0x%x", *linux);
    else
        LOG_ERR("No linux kernel");

    if (atf)
        LOG_INFO("ATF: 0x%x", *atf);
    else
        LOG_INFO("ATF: None");

    if (tee)
        LOG_INFO("TEE: 0x%x", *tee);
    else
        LOG_INFO("TEE: None");

    if (ramdisk)
        LOG_INFO("RAMDISK: 0x%x", *ramdisk);
    else
        LOG_INFO("RAMDISK: None");

    plat_preboot_cleanup();
    tr_stamp_end(TR_TOTAL);
    tr_stamp_end(TR_DT_PATCH);

    tr_print_result();

    plat_wdog_kick();

    /* printf("b"); */

    if (atf && dtb && linux)
    {
        LOG_DBG("ATF boot");
        arch_jump_atf((void *)(uintptr_t) *atf,
                      (void *)(uintptr_t) NULL);
    }
    else if(dtb && linux && !atf && tee)
    {
        LOG_INFO("TEE boot");
        arch_jump_linux_dt((void *)(uintptr_t) *tee,
                           (void *)(uintptr_t) *dtb);
    }
    else if(dtb && linux)
    {
        arch_jump_linux_dt((void *)(uintptr_t) *linux,
                           (void *)(uintptr_t) *dtb);
    }

    while (1);
}
