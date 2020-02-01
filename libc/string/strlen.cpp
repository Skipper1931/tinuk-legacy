// strlen() implementation for the Tinuk kernel
// Copyright (C) 2020 Skipper1931 (GPL-3.0 License)

#include <string.h>
 
size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}