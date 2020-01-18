// TTY driver header for the Tinuk kernel
// These functions are implemented in ../arch/i386/tty.cpp (for IA-32)
// Copyright (C) 2020 Skipper1931 (GPL-3.0 License)

#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H
 
#include <stddef.h>
 
void tty_init(void);
void tty_putchar(char c);
void tty_write(const char* data, size_t size = 0);
 
#endif