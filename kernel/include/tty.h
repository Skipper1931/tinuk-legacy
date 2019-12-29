// TTY driver header for the Tinuk kernel

#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H
 
#include <stddef.h>
 
void tty_init(void);
void tty_putchar(char c);
void tty_write(const char* data, size_t size = 0);
 
#endif