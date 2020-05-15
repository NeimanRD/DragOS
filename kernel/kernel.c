#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <i386/tty.h>

void kernel_main()
{
    tty_init();
    tty_write_string("Hello, World!");
}