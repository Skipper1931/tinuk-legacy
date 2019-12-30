// Entry point for the Tinuk kernel
// Copyright (c) 2019 Skipper1931

#include <stdio.h>
#include <kernel/include/tty.h>
#include <kernel/include/multiboot.h>

extern "C"
{
	void kmain(multiboot_info_t* mb_info, unsigned int magic)
	{
		if (magic != 732803074) return; // magic value put by GRUB isn't valid, thus something went wrong
		
		tty_init();
		printf("\n");

		printf("Hello, kernel World!\n");
	}
}