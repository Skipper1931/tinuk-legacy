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
.type _start, @function
_start:
	movl $stack_top, %esp

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call _Z5kmainv

	# Hang if kmain unexpectedly returns.

	cli
	hlt

	#call func
	#jmp 0x800f12
	
failsafe:
	jmp failsafe

func:
	pushl %ebp
	movl %esp, %ebp
	subl $20, %esp

	movl %esp, %eax
	movl %esp, %ebx
	subl $8, %eax
	subl $16, %ebx

	movl $12, (%eax)
	movl $8, (%ebx)

	movl (%eax), %ecx
	movl (%ebx), %edx

	addl %edx, %ecx
	ret


.size _start, . - _start
