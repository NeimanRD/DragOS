#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H
 
#include <stddef.h>
#include <drivers/vga.h>
#include <stdint.h>

extern uint8_t terminal_color;

void tty_init(v_color_t fg, v_color_t bg);
void tty_putc(char c, v_color_t color);
void tty_write(const char* data, size_t size, v_color_t color);
void tty_write_string(const char* str);
void tty_color_write(const char* data, v_color_t fg);
void tty_scroll();
 
#endif

