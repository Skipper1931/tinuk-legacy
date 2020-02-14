#include "print.h"
#include <kernel/paging.h>

void no_64() {
    print_clear();
    print("You are running a CPU that is not 64-bit (x86-64/amd64).\nIn order to use TinukOS/Karyon, your processor must be 64-bit!\n");
}

void bootmain() {
    print_clear();
    print("Karyon Kernel Stage 2 Bootloader\n");


}