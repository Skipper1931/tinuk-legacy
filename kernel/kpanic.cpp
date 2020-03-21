#include <kernel/panic.h>
#include <stdio.h>

extern "C" void hang(); // links the assembly hang func in arch/.../hang.asm to this

void kpanic(const char* msg) {
    printf("KERNEL PANIC: %s", msg);
    hang();
}