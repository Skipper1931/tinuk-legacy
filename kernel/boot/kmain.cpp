// Entry point for the Tinuk kernel
// Copyright (C) 2020 Skipper1931 (GPL-3.0 License)

#include <stdint.h>
#include <stdio.h>
#include <kernel/include/vga-txt.h>
#include <kernel/include/multiboot.h>
#include <string.h>

bool get_mbi_flag(multiboot_info_t* mbi, uint8_t bit) {
	return (mbi->flags >> (12-bit)) & 1;
}

extern "C"
{
	void kmain(multiboot_info_t* mb_info, unsigned int mb_magic)
	{		
		vga_txt_init();

		if (mb_magic != MULTIBOOT_BOOTLOADER_MAGIC) { // magic value put by GRUB isn't valid, thus something went wrong
			printf("ERROR: Invalid GRUB Magic Value\n");
			return;
		}
		if (!get_mbi_flag(mb_info, 6)) {
			printf("ERROR: GRUB mmap not present\n");
			return;
		}

		printf("\nGRUB Physical Memory Map:\n");
		multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mb_info->mmap_addr;
		while ((unsigned int)mmap < mb_info->mmap_addr + mb_info->mmap_length) {
			printf("Addr: 0x%llx  ", mmap->addr);
			printf("Length: 0x%llx  ", mmap->len);

			char type_msg[6];

			switch (mmap->type)
			{
			case 1:
				memcpy(type_msg, "AVAIL", 6);
				break;
			case 3:
				memcpy(type_msg, "ACPIR", 6);
				break;
			case 4:
				memcpy(type_msg, "HIBER", 6);
				break;
			case 5:
				memcpy(type_msg, "BADRM", 6);
				break;
			
			default:
				memcpy(type_msg, "RESRV", 6);
				break;
			}

			printf("Type: %s", type_msg);
			printf(" (0x%x)\n", mmap->type);

			mmap = (multiboot_memory_map_t*) ((unsigned int)mmap + (mmap->size + 4)); // mmap->size doesn't take itself into account so it (32-bit so 4 bytes) needs to be added
		}
		printf("\n");
		
		printf("That's all folks!!\n");
	}
}