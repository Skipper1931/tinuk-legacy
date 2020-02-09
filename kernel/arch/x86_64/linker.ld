/* The bootloader will look at this image and start execution at the symbol
   designated at the entry point. */
ENTRY(_start32)

SEARCH_DIR(../sysroot/usr/lib/)

KERNEL_LMA = 1M;
KERNEL_VMA = 0xFFFF800000000000;

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
	/* Put the 32-bit bootstrap code at the 1MiB physical address. We'll later map the rest to kernel-space
	   virtual memory */
	. = KERNEL_LMA;

	/*.boot ALIGN(4096): 
	{
	}

	. += KERNEL_VMA;*/
	
	.text ALIGN(4096) : 
	{
		*(.multiboot)
		*(.text)
	}

	/* Read-only data. */
	.rodata ALIGN(4096) : 
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data ALIGN(4096) : 
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss ALIGN(4096) : 
	{
		*(COMMON)
		*(.bss)
	}

	/* The compiler may produce other sections, put them in the proper place in
	   in this file, if you'd like to include them in the final kernel. */
}