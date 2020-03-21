// loader32.elf entrypoint
// Copyright (C) 2020 Skipper1931 (GPL-3.0 License)

#include "print.h"
#include "loader.h" 
#include <kernel/multiboot.h>
#include <string.h>

const char* KERNEL_STR = "KARYON_KERNEL";

void no_64() {
    print_clear();
    print("ERROR: You are running a CPU that is not 64-bit (x86-64/amd64).\nIn order to use TinukOS/Karyon, your processor must be 64-bit!\n");
    asm_hang();
}

void bootmain(int huge_pages, multiboot_info_t* mb_info, unsigned int mb_magic) {

    print_clear();
    print("Stage 2 Bootloader (loader32.elf)\n\n");

    if(mb_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        print("ERROR: GRUB magic invalid\n");
        asm_hang();
    }

    if(huge_pages == 0) {
        print("WARNING: This CPU does not support 1GiB pages (pdpe1gb). This may cause crashes.");
    }

    if (mb_info->flags & MULTIBOOT_INFO_MODS) {
        print("Searching for kernel amongst loaded modules...\n");
        for(int mod_num = 0; mod_num < mb_info->mods_count; mod_num++) {
            multiboot_module_t* mod = (multiboot_module_t*)(mb_info->mods_addr + (mod_num * sizeof(multiboot_module_t)));
            print("Checking module ");
            print(mod->cmdline);
            print("\n");

            if(strcmp(mod->cmdline, KERNEL_STR)) {
                print("Kernel module found\n");
                enter_64(mod);
            }
        }
        print("ERROR: GRUB did not load kernel module");
        asm_hang();
    }
    else {
        print("ERROR: GRUB did not load any modules, including the kernel\n");
        asm_hang();
    }
}
