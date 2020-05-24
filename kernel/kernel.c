#include <stdint.h>
#include <libk/stdio.h>
#include <libk/string.h>
#include <kernel/tty.h>

void kernel_main()
{
    tty_init();
    for (int i = 0; i < 26; i++)
    {
        printf("%i\n", i);
    }
}