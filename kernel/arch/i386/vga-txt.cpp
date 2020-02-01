// VGA Text Mode driver implementation (VGA Text Mode, IA-32) for the Tinuk kernel
// Copyright (C) 2020 Skipper1931 (GPL-3.0 License)

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/include/vga-txt.h>

#include "vga.h"

static const uint8_t VGA_WIDTH = 80;
static const uint8_t VGA_HEIGHT = 25;
static uint16_t *const VGA_MEMORY = (uint16_t *)0xB8000;

static uint8_t vga_txt_row;
static uint8_t vga_txt_column;
static uint8_t vga_txt_color;
static uint16_t *vga_txt_buffer;

void vga_txt_init(void)
{
	vga_txt_row = 0;
	vga_txt_column = 0;
	vga_txt_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	vga_txt_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			vga_txt_buffer[index] = vga_entry(' ', vga_txt_color);
		}
	}

	vga_txt_write("Initialized VGA Text Mode driver\n");
}

void vga_txt_setcolor(uint8_t color)
{
	vga_txt_color = color;
}

void vga_txt_scroll()
{
	// TODO: Implement
}

void vga_txt_putentryat(unsigned char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	vga_txt_buffer[index] = vga_entry(c, color);
}

void vga_txt_putchar(char c)
{
	unsigned char uc = c;

	if (uc == '\n')
	{
		vga_txt_row++;
		vga_txt_column = 0;
	}
	else if (uc == '\t')
	{
		int offset = vga_txt_column % 8;
		if(offset == 0)
			offset = 8;

		vga_txt_column += offset; // move to the next eigth offset into the row

		if (vga_txt_column >= VGA_WIDTH)
		{
			vga_txt_column = VGA_WIDTH - 1;
		}
	}
	else
	{
		vga_txt_putentryat(uc, vga_txt_color, vga_txt_column, vga_txt_row);

		if (++vga_txt_column == VGA_WIDTH)
		{
			vga_txt_column = 0;
			if (++vga_txt_row == VGA_HEIGHT)
				vga_txt_row = 0;
		}
	}
}

void vga_txt_write(const char *data, size_t size)
{
	if (size == 0) // allows user to do vga_txt_write(string) without having to specify length themselves
		size = strlen(data);

	for (size_t i = 0; i < size; i++)
		vga_txt_putchar(data[i]);
}
