#include <kernel/panic.h>
#include <drivers/tty/log.h>
#include <lib/print.h>
#include <stdint.h>

static void print_stack_trace();

void panic(const char *msg)
{
    logf(kernel, "System Panic: %s\n", msg);
    printf("*** System Panic: %s\n", msg);
    printf("***\n");
    logf(kernel, "Halting system\n");
    for (;;);
}
