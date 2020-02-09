BITS 32

SECTION .bss
resb 16384  ; 16 KiB stack
stack_top:

SECTION .rodata
gdt64:
    dq 0
.code: equ $ - gdt64
    dq (1<<44) | (1<<47) | (1<<41) | (1<<43) | (1<<53)
.data: equ $ - gdt64
    dq (1<<44) | (1<<47) | (1<<41)
.pointer:
    dw .pointer - gdt64 - 1
    dq gdt64

SECTION .text
GLOBAL _start32
EXTERN _start64
EXTERN check_64
EXTERN setup_page_tables
_start32:
    mov esp, stack_top
    mov esi, eax
    mov edi, ebx

    mov word [0xB8000], 0x0000

    call check_64
    call setup_page_tables

    ; move page table address to cr3
    mov cr3, eax

    ; enable PAE
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; set the long mode bit
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; enable paging
    mov eax, cr0
    or eax, 1 << 31
    or eax, 1 << 16
    mov cr0, eax
    
    lgdt [gdt64.pointer]
    mov ax, gdt64.data
    mov ss, ax
    mov ds, ax
    mov es, ax

    jmp gdt64.code:_start64