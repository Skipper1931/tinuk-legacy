BITS 64

; The kernel entry point.
SECTION .entry
GLOBAL _start64
EXTERN _init
EXTERN kmain

_start64:
	; Save multiboot info in case the constructors use them for some reason
	push rsi
	push rdi

	; Call the global constructors.
	; call _init

	pop rdi
	pop rsi
	; Transfer control to the main kernel.
	lea rax, [rel kmain]
	call rax

