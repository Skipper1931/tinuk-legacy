BITS 64

; The kernel entry point.
SECTION .text
GLOBAL _start64
GLOBAL asm_kpanic
EXTERN _init
EXTERN kmain

_start64:
	; Save multiboot info in case the constructors use them for some reason
	push rsi
	push rdi

	; Call the global constructors.
	lea rax, [rel _init]
	call rax

	pop rdi
	pop rsi
	; Transfer control to the main kernel.
	lea rax, [rel kmain]
	call rax

asm_kpanic:
	; Hang if kmain unexpectedly returns OR if we call kpanic.
	cli
.hang:
	hlt
	jmp .hang
