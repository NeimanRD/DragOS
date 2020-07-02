#ifndef PRINT_H
#define PRINT_H

// A minimal stdio header for the kernel

#include <drivers/vga.h>
#include <stdarg.h>

int printf(const char *format, ...);
void putchar(char ic, v_color_t color);
void puts(const char *string);
int cprintf_internal(v_color_t color, const char* format, va_list args);
int cprintf(v_color_t color, const char *format, ...);


#endif