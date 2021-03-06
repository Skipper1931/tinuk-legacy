// putchar() implementation for the Tinuk kernel
// Copyright (C) 2020 Skipper1931 (GPL-3.0 License)

#include <stdio.h>
 
#if defined(__is_libk)
#include <kernel/vga-txt.h>
#endif
 
int putchar(int ic) {
#if defined(__is_libk)
	char c = (char) ic;
	vga_txt_write(&c, sizeof(c));
#else
	// TODO: Implement stdio and the write system call.
#endif
	return ic;
}