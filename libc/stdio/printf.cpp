// printf() implementation for the Tinuk kernel
// Copyright (C) 2020 Skipper1931 (GPL-3.0 License)

#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static bool print(const char *data, size_t length)
{
	const unsigned char *bytes = (const unsigned char *)data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
			return false;
	return true;
}


void format_hex(unsigned long long int val, unsigned char width, char* buffer) {
	int reps = width / 4;
	unsigned long long int mask = 0x000000000000000F;
	mask = mask << (width - 4); // shift the mask over the the most signifigant byte

	for(int i = 0; i < reps; i++) {
		unsigned char nibble = (val & mask) >> (width - 4); // get only the first four bytes
		buffer[i] = "0123456789abcdef"[nibble];				// append that corresponding hex code to the buffer
		val = val << 4; 									// shift over for next four bytes
	}
}

int printf(const char *__restrict format, ...)
{
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	bool parsing_format = false; // set to true if we need multiple loops for one format specifier
	uint8_t length = 1; // 0-3 (8/16/32/64 bits)

	while (*format != '\0')
	{
		size_t maxrem = INT_MAX - written;

		if ((format[0] != '%' || format[1] == '%') && !parsing_format)
		{
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount)
			{
				// TODO: Set errno to EOVERFLOW or throw exceptions
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char *format_begun_at = format++;

		if(*format == 'l') { // make it loooonger
				length++;
				if (length > 3) {
					// TODO: Throw exception
					return -1;
				}
				parsing_format = true; // we'll need another go-around
				continue;
		}

		if (*format == 'c') { // char
			format++;
			char c = (char)va_arg(parameters, int /* char promotes to int */);
			if (!maxrem)
			{
				// TODO: Set errno to EOVERFLOW or throw exception
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		}
		else if (*format == 'x') { // hexadecimal
			format++;
			uint8_t _width;
			uint64_t num;

			if(length == 0) {
				_width = 8;
				num = (uint64_t)va_arg(parameters, int); // promotes to int
			}
			else if (length == 1) {
				_width = 16;
				num = (uint64_t)va_arg(parameters, int); // promotes to int
			}
			else if (length == 2) {
				_width = 32;
				num = (uint64_t)va_arg(parameters, long int);
			}
			else if (length == 3) {
				_width = 64;
				num = (uint64_t)va_arg(parameters, long long int);
			}
			else {	//invalid length val for some reason
				// TODO: Throw exception
				return -1;
			}
			size_t len = _width / 4;
			
			char buffer[len];
			format_hex(num, _width, buffer);

			if (maxrem < len)
			{
				// TODO: Throw error
				return -1;
			}
			if (!print(buffer, len))
				return -1;
			written += len;
		}
		else if(*format == 's') { // string
			format++;
			const char *str = va_arg(parameters, const char *);
			size_t len = strlen(str);
			if (maxrem < len)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		}
		else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}

		parsing_format = false; // if we get here we're done
	}

	va_end(parameters);
	return written;
}
