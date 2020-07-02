#include <lib/print.h>
#include <drivers/tty.h>
#include <drivers/vga.h>

void putchar(char ic, v_color_t color)
{
    tty_color_write(&ic, color);
}