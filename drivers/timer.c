#include <cpu/idt.h>
#include <drivers/timer.h>
#include <lib/print.h>
#include <drivers/io.h>
#include <drivers/tty/log.h>

int tick = 0;

static void timer_callback(regs_t *regs)
{
    tick++;
    logf(device, "Tick: %i", tick);
}

void init_timer(uint32_t frequency)
{
    register_interrupt_handler(32, &timer_callback);

    uint32_t divisor = 1193180 / frequency;

    outb(0x43, 0x36);

    uint8_t l = (uint8_t) (divisor & 0xFF);
    uint8_t h = (uint8_t) ((divisor >> 8) & 0xFF);

    outb(0x40, l);
    outb(0x40, h);
    logf(cpu, "Initialized the timer\n");
}