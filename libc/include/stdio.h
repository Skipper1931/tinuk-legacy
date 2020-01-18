// Standard I/O Functions
// Copyright (C) 2020 Skipper1931 (GPL-3.0 License)

#ifndef _STDIO_H
#define _STDIO_H 1
 
#include <sys/cdefs.h>
 
#define EOF (-1)
 
#ifdef __cplusplus
extern "C" {
#endif
 
int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);
 
#ifdef __cplusplus
}
#endif
 
#endif