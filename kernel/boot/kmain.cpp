// Entry point for the Tinuk kernel
// Copyright (c) 2019 Skipper1931

#include <stdint-gcc.h>
#include <stdio.h>
#include <kernel/include/tty.h>
#include <kernel/include/multiboot.h>

bool get_mbi_flag(multiboot_info_t* mbi, uint8_t bit) {
	return (mbi->flags >> (12-bit)) & 1;
}

extern "C"
{
	void kmain(multiboot_info_t* mb_info, unsigned int mb_magic)
	{
		if (mb_magic != MULTIBOOT_BOOTLOADER_MAGIC) return; // magic value put by GRUB isn't valid, thus something went wrong
		
		tty_init();

		printf("\n");
		printf("Hello, kernel World!\n");

		if (get_mbi_flag(mb_info, 6)) printf("true"); else printf("false");
		printf("\n");

		multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mb_info->mmap_addr;
		while (mmap < (multiboot_memory_map_t*)(mb_info->mmap_addr + mb_info->mmap_length)) {
			multiboot_memory_map_t mmap_t = *mmap;

			mmap = (multiboot_memory_map_t*) mmap + (mmap->size + 4); // mmap->size doesn't take itself into account so it (32-bit so 4 bytes) needs to be added
		}
	}
}