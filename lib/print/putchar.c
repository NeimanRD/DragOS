#include <lib/print.h>
#include <drivers/tty.h>

void putchar(int ic)
{
    char c = (char) ic;
    tty_write(&c, sizeof(c));
}