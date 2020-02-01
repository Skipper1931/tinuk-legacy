// puts() implementation for the Tinuk kernel
// Copyright (C) 2020 Skipper1931 (GPL-3.0 License)

#include <stdio.h>
 
int puts(const char* string) {
	return printf("%s\n", string);
}