#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/tty.h>

void kernel_main()
{
    tty_init();
    tty_write_string("Hello, World!");
}