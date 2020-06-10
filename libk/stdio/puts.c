#include <libk/stdio.h>
#include <modules/tty.h>

void puts(const char *string)
{
    tty_write_string(string);
}