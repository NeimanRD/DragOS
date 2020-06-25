#include <cpu/irq.h>
#include <cpu/isr.h>
#include <drivers/timer.h>
#include <lib/print.h>
#include <drivers/io.h>

int tick = 0;
unsigned int seconds = 0;

static void timer_handler(regs_t *regs)
{
    tick++;
    if (tick % 100 == 0)
    {
        seconds++;
        printf("%i seconds has passed\n", seconds);
    }
}

void init_timer(uint32_t frequency)
{
    irq_install_handler(0, &timer_handler);

    uint32_t divisor = 1193180 / frequency;

    outb(0x43, 0x36);

    uint8_t l = (uint8_t) (divisor & 0xFF);
    uint8_t h = (uint8_t) ((divisor >> 8) & 0xFF);

    outb(0x40, l);
    outb(0x40, h);
}