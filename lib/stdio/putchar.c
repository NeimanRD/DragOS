#include <lib/stdio.h>
#include <drivers/tty.h>

void putchar(int ic)
{
    char c = (char) ic;
    tty_write(&c, sizeof(c));
}