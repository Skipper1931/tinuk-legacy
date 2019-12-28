// Entry point for the Tinuk kernel
// Copyright (c) 2019 Skipper1931

#include <stdio.h>
#include <kernel/include/tty.h>
#include <stack.h>

extern "C"
{
	void kmain(void)
	{
		tty_init();
		printf("\n");

		printf("Hello, kernel World!\n");
	}
}