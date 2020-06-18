#include <stdint.h>
#include <lib/print.h>
#include <lib/string.h>
#include <drivers/tty.h>

void kernel_main()
{
    tty_init();
    printf("Test");
}