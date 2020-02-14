#include "print.h"
#include "../vga.h"

const unsigned char width = 80;
const unsigned char height = 25;

short int* buf = 0xB8000;

unsigned char row = 0, column = 0;
unsigned char color;

void print_clear() {
    color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

    for (unsigned char y = 0; y < height; y++)
	{
		for (unsigned char x = 0; x < width; x++)
		{
			const int index = y * width + x;
			buf[index] = vga_entry(' ', color);
		}
	}

    row = 0;
    column = 0;
}

int print(const char* s) {
    unsigned int x = 0;

    while(1) {
        if (s[x] == '\0')
            return 0;

        if (s[x] == '\n') {
            row++;
            column = 0;
            x++;
            continue;
        }

        unsigned int offset = row * width + column;

        buf[offset] = vga_entry(s[x], color);

        if(++column == width) {
            column = 0;
            if(++row == height) {
                print_clear();
                print(s);
            }
        }

        x++;
    }

    return -1;
}