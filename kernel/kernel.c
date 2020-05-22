#include <libk/stdio.h>
#include <libk/string.h>
#include <kernel/tty.h>

void kernel_main()
{
    tty_init();
    puts("Hello!\n");
    puts("Hello");
}