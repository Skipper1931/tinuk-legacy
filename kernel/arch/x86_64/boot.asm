BITS 64

; The kernel entry point.
SECTION .text
GLOBAL _start64
GLOBAL asm_kpanic
EXTERN _init
EXTERN kmain

_start64:
	; Put multiboot info struct and magic num (both from GRUB) onto stack for kmain
	;push eax
	;push ebx

	xchg rax,rax

	; Call the global constructors.
	call _init

	; Transfer control to the main kernel.
	call kmain

asm_kpanic:
	; Hang if kmain unexpectedly returns OR if we call kpanic.
	cli
hang:
	hlt
	jmp hang