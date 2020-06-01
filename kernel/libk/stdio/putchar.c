#include <libk/stdio.h>
#include <modules/tty.h>

void putchar(int ic)
{
    char c = (char) ic;
    tty_write(&c, sizeof(c));
}