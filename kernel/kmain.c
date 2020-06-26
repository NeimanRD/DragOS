#include <lib/print.h>
#include <drivers/tty.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/irq.h>
#include <drivers/timer.h>
#include <lib/stdlib.h>

void kernel_main()
{
    init_gdt();
    init_idt();
    init_irq();
    asm volatile("sti");
    init_timer(100);
    tty_init();
    
}