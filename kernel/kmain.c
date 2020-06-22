#include <lib/print.h>
#include <drivers/tty.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>

void kernel_main()
{
    init_gdt();
    init_idt();
    tty_init();
    printf("Test\n");
}