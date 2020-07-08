#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <drivers/tty/log.h>

void init_dt()
{
    init_gdt();
    logf(cpu, "Initialized GDT\n");
    init_idt();
    logf(cpu, "Initialized IDT\n");
}