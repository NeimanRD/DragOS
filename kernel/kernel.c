#include <libk/stdio.h>
#include <libk/string.h>
#include <kernel/tty.h>

void kernel_main()
{
    tty_init();
    printf("Hello %i hello", 10);
}