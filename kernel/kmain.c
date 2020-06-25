#include <lib/print.h>
#include <drivers/tty.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/irq.h>
#include <drivers/timer.h>

void kernel_main()
{
    init_gdt();
    init_idt();
    init_irq();
    init_timer(100);
    asm volatile("sti");
    tty_init();
    printf("Test\n");
}