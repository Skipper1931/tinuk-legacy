// VGA Text Mode driver header for the Tinuk kernel
// These functions are implemented in ../arch/i386/vga_txt.cpp (for IA-32)
// Copyright (C) 2020 Skipper1931 (GPL-3.0 License)

#ifndef _KERNEL_vga_txt_H
#define _KERNEL_vga_txt_H
 
#include <stddef.h>
 
void vga_txt_init(void);
void vga_txt_putchar(char c);
void vga_txt_write(const char* data, size_t size = 0);
 
#endif