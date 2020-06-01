#include <libk/stdio.h>
#include <kernel/tty.h>

void puts(const char *string)
{
    tty_write_string(string);
}