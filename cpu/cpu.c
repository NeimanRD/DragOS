#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/irq.h>

void init_dt()
{
    init_gdt();
    init_idt();
    init_irq();
    asm volatile("sti");
}