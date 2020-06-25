#ifndef IRQ_H
#define IRQ_H

#include <cpu/isr.h>

void init_irq();
void irq_uninstall_handler(int irq);
void irq_install_handler(int irq, void (*handler)(regs_t *r));

#endif