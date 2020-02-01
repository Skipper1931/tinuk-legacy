#include <kernel/panic.h>
#include <stdio.h>

extern "C" void asm_kpanic(); // links the asm_kpanic func in arch/i386/boot.S to this

void kpanic(const char* msg) {
    printf("KERNEL PANIC: %s", msg);
    asm_kpanic();
}