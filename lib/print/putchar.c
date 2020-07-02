#include <lib/print.h>
#include <drivers/tty.h>
#include <drivers/vga.h>

void putchar(int ic, v_color_t color)
{
    char c = (char) ic;
    tty_color_write(&c, color);
}