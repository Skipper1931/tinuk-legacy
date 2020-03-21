#include "loader.h"
#include "../paging.h"
#include <kernel/elf64.h>
#include "print.h"

#define BINARY_MAX (1024 * 1024 * 2)

pt_entry ptl4[512] __attribute__ ((aligned (4096)));
pt_entry ptl3_lower[512] __attribute__ ((aligned (4096)));
pt_entry ptl2_lower[512] __attribute__ ((aligned (4096)));
pt_entry ptl3_upper[512] __attribute__ ((aligned (4096)));
pt_entry ptl2_upper[512] __attribute__ ((aligned (4096)));

unsigned char kernel_paddr[BINARY_MAX] __attribute__ ((aligned (4096)));

unsigned long long int swap_bytes(unsigned long long int x) {
    unsigned char x0 = (unsigned char)x;
    unsigned char x1 = (unsigned char)(x >> 8);
    unsigned char x2 = (unsigned char)(x >> 16);
    unsigned char x3 = (unsigned char)(x >> 24);
    unsigned char x4 = (unsigned char)(x >> 32);
    unsigned char x5 = (unsigned char)(x >> 40);
    unsigned char x6 = (unsigned char)(x >> 48);
    unsigned char x7 = (unsigned char)(x >> 56);

    unsigned long long swapped = 0;
    swapped &= x7;
    swapped &= x6 << 8;
    swapped &= x5 << 16;
    swapped &= x4 << 24;
    swapped &= x3 << 32;
    swapped &= x2 << 40;
    swapped &= x1 << 48;
    swapped &= x0 << 56;

    return swapped;
}

set_up_paging_return set_up_paging(Elf64_Ehdr* ehdr) {
    Elf64_Phdr* phdr = ehdr + ehdr->e_phoff;
    if(phdr->p_memsz > BINARY_MAX) {
        print("ERROR: Kernel binary too large\n");
        asm_hang();
    }

    // Zero-out page tables and kernel memory area

    for(int i = 0; i < 512; i++) {
        pt_entry temp;

        temp.accessed = 0;
        temp.addr = 0;
        temp.unusedA = 0;
        temp.unusedB = 0;
        temp.dirty = 0;
        temp.disable_cache = 0;
        temp.global = 0;
        temp.huge = 0;
        temp.no_exec = 0;
        temp.present = 0;
        temp.user_access = 0;
        temp.writable = 0;
        temp.write_thru = 0;

        ptl4[i] = temp;
        ptl3_lower[i] = temp;
        ptl2_lower[i] = temp;
        ptl3_upper[i] = temp;
        ptl2_upper[i] = temp;
    }

    for(int i = 0; i < BINARY_MAX; i++) {
        kernel_paddr[i] = 0;
    }

    ptl4[0].present = 1;
    ptl4[0].writable = 1;
    ptl4[0].addr = swap_bytes((long long int)ptl3_lower >> 11);

    ptl3_lower[0].present = 1;
    ptl3_lower[0].writable = 1;
    ptl3_lower[0].addr = swap_bytes((long long int)ptl2_lower >> 11);

    ptl2_lower[0].present = 1;
    ptl2_lower[0].write_thru = 1;
    ptl2_lower[0].huge = 1;
    ptl2_lower[0].addr = 0;

    ptl4[512].present = 1;
    ptl4[512].global = 1;
    ptl4[512].writable = 1;
    ptl4[512].addr = swap_bytes((long long int)ptl3_upper >> 11);

    ptl3_upper[0].present = 1;
    ptl3_upper[0].global = 1;
    ptl3_upper[0].writable = 1;
    ptl3_upper[0].addr = swap_bytes((long long int)ptl2_upper >> 11);

    ptl2_upper[0].present = 1;
    ptl2_upper[0].global = 1;
    ptl2_upper[0].writable = 1;
    ptl2_upper[0].huge = 1;
    ptl2_upper[0].addr = swap_bytes((long long int) kernel_paddr >> 11);

    set_up_paging_return supr;
    supr.kernel_paddr = kernel_paddr;
    supr.ptl4 = ptl4;
    return supr;
}