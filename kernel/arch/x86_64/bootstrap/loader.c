#include "loader.h"
#include "print.h"
#include <kernel/multiboot.h>

void (*get_entry())(multiboot_module_t* mod) {
    // TODO
}

void enter_64(multiboot_module_t* mod) {
    print("Loading kernel...");
    void (*entry_ptr)() = get_entry(mod);

    asm_hang();
}