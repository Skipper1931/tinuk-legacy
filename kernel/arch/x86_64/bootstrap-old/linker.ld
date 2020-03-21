/* The bootloader will look at this image and start execution at the symbol
   designated at the entry point. */
ENTRY(_start32)

LOADER_ADDR = 1M;

/* Tell where the various sections of the object files will be put in the final
   loader image. */
SECTIONS
{
	. = LOADER_ADDR;

    .multiboot :
    {
        *(.multiboot)
    }

	.text :
	{
        *(.text)
	}

	/* Read-only data. */
	.rodata :
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data :
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss :
	{
		*(COMMON)
		*(.bss)
	}
}
