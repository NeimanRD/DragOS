#include <libk/stdio.h>
#include <kernel/tty.h>

void putchar(int ic)
{
    char c = (char) ic;
    tty_write(&c, sizeof(c));
}