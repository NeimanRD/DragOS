#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H
 
#include <stddef.h>
#include "vga.h"
 
void tty_init(void);
void tty_putc(char c);
void tty_write(const char* data, size_t size);
void tty_write_string(const char* data);
void tty_scroll();
 
#endif

