#ifndef _H_LOADER_LOADER
#define _H_LOADER_LOADER 1

// Contains misc. functions (primarily get_entry and setup_64) needed by the loader

#include <kernel/multiboot.h>

extern void asm_hang();

void (*get_entry())(multiboot_module_t* mod);
void enter_64(multiboot_module_t* mod);

#endif