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
    init_timer(100);

    init_pmm(mbd->mem_upper);
    init_vmm();
    uint32_t i = mbd->mmap_addr;
    while (i < mbd->mmap_addr + mbd->mmap_length)
    {
        multiboot_memory_map_t *me = (multiboot_memory_map_t*) i;
        if (me->type == 1)
        {
            uint32_t j;
            for (j = me->base_addr_low; j < me->base_addr_low+me->length_low; j += 0x1000)
            {
                pmm_free_page(j);
            }
        }

        i += me->size + sizeof (uint32_t);
    }

    uint32_t *ptr = (uint32_t*) 0xA0000000;
    uint32_t page_fault = *ptr;
}