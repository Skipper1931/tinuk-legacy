# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.global asm_kpanic
.type _start, @function
.type asm_kpanic, @function
_start:
	movl $stack_top, %esp

	# Put multiboot info struct and magic num (both from GRUB) onto stack for kmain
	push %eax
	push %ebx

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kmain

asm_kpanic:
	# Hang if kmain unexpectedly returns OR if we call kpanic.
	cli
hang:
	hlt
	jmp hang


.size _start, . - _start
