%define MAGIC 0x1BADB002
%define FLAGS 0b00000000000000000000000000000000

BITS 32

SECTION .multiboot
align 8             ; 64-bit (8 bytes) align the header

dd MAGIC
dd FLAGS
dd 0x100000000 - (MAGIC + FLAGS)     ; checksum