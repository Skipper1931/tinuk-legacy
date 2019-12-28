// Entry point for the Tinuk kernel
// Copyright (c) 2019 Skipper1931

#include <stdio.h>
#include <kernel/dev/tty.h>
#include <stack.h>

void kmain(void) {
	tty_init();
	printf("\n");

	printf("Hello, kernel World!\n");
}
