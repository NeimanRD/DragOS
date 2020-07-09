#include <kernel/panic.h>
#include <drivers/tty/log.h>
#include <lib/print.h>
#include <stdint.h>

void panic(const char *msg)
{
    logf(kernel, "System Panic: %s\n", msg);
    cprintf(COLOR_RED, "System Panic: %s ", msg);
    logf(kernel, "Halting system\n");
    for (;;);
}
