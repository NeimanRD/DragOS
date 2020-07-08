#include <kernel/panic.h>
#include <drivers/tty/log.h>
#include <kernel/elf.h>
#include <lib/print.h>
#include <stdint.h>

static void print_stack_trace();

extern elf_t kernel_elf;

void panic(const char *msg)
{
    logf(kernel, "System Panic: %s\n", msg);
    printf("*** System Panic: %s\n", msg);
    print_stack_trace();
    printf("***\n");
    logf(kernel, "Halting system\n");
    for (;;);
}

static void print_stack_trace()
{
    uint32_t *ebp, *eip;
    asm volatile ("mov %%ebp, %0" : "=r" (ebp));
    while (ebp)
    {
        eip = ebp + 1;
        printf("   [%x] %s\n", *eip, elf_lookup_symbol(*eip, &kernel_elf));
        logf(kernel, "   [%x] %s\n", *eip, elf_lookup_symbol(*eip, &kernel_elf));
        ebp = (uint32_t*) *ebp;
    }
}