#include <lib/print.h>
#include <drivers/tty.h>

void puts(const char *string)
{
    tty_write_string(string);
}