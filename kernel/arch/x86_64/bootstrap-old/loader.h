#ifndef _H_LOADER_LOADER
#define _H_LOADER_LOADER 1

#include <kernel/multiboot.h>
#include <kernel/elf64.h>
#include "../paging.h"

typedef struct {
    pt_entry* ptl4;
    void* kernel_paddr;
} set_up_paging_return;

extern void asm_hang();
extern void enable_paging();

void enter_64(multiboot_module_t* mod);
set_up_paging_return set_up_paging(Elf64_Ehdr* ehdr);

#endif