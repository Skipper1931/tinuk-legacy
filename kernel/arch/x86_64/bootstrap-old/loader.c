#include "loader.h"
#include "print.h"
#include <kernel/multiboot.h>
#include <kernel/elf64.h>
#include <string.h>

void check_elf(Elf64_Ehdr* elf_ehdr) {
    if(elf_ehdr->e_ident.El_MAG0 != 0x7f) {
        goto bad_mag;
    }
    if(elf_ehdr->e_ident.El_MAG1 != 'E') {
        goto bad_mag;
    }
    if(elf_ehdr->e_ident.El_MAG2 != 'L') {
        goto bad_mag;
    }
    if(elf_ehdr->e_ident.El_MAG3 != 'F') {
bad_mag:print("ERROR: Invalid ELF magic\n");
        asm_hang();
    }

    /*char str[4];
    str[0] = elf_ehdr->e_ident.El_MAG1;
    str[1] = elf_ehdr->e_ident.El_MAG2;
    str[2] = elf_ehdr->e_ident.El_MAG3;
    str[3] = '\0';
    print(str);*/
}

void (*load_kernel(Elf64_Ehdr* elf_ehdr))() {
    return (void(*)())elf_ehdr->e_entry;
}

void enter_64(multiboot_module_t* mod) {
    Elf64_Ehdr* elf_ehdr = mod->mod_start; 
    check_elf(elf_ehdr);

    print("Setting up page tables...");
    set_up_paging_return supr = set_up_paging(elf_ehdr);
    print("Done\n");

    print("Enabling paging...");
    enable_paging();
    print("Done\n");

    print("Loading kernel...\n");
    asm_hang();
}