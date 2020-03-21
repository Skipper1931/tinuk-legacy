SECTION .text
GLOBAL hang

hang:
	; Hang if kmain unexpectedly returns OR if we call kpanic.
	cli
.loop:
	hlt
	jmp .loop
