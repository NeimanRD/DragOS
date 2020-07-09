#include <lib/print.h>
#include <cpu/cpu.h>
#include <drivers/tty.h>
#include <drivers/timer.h>
#include <multiboot.h>
#include <drivers/vga.h>
#include <drivers/tty/log.h>
#include <mm/physical.h>
#include <mm/virtual.h>


void kernel_main(multiboot_info_t* mbd, unsigned int magic)
{
    tty_init(COLOR_WHITE, COLOR_BLACK);
    init_dt();
    asm volatile("int $0x3");
    init_timer(20);
    init_pmm(mbd->mem_upper);
    init_vmm();
}