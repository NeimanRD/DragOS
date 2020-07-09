#include <lib/print.h>
#include <drivers/tty.h>
#include <drivers/vga.h>

void putchar(char c, v_color_t color)
{
    tty_putc(c, color);
}