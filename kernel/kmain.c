#include <lib/print.h>
#include <cpu/cpu.h>
#include <drivers/tty.h>
#include <drivers/timer.h>
#include <multiboot.h>
#include <drivers/vga.h>
#include <drivers/tty/log.h>
#include <mm/physical.h>
#include <mm/virtual.h>

char* mem_type[] = 
{
    "Available",
    "Reserved",
    "ACPI",
    "Reserved",
    "Defective",
    "Reserved"
};

void kernel_main(multiboot_info_t* mbd, unsigned int magic)
{
    tty_init(COLOR_WHITE, COLOR_BLACK);
    
    if (MULTIBOOT_BOOTLOADER_MAGIC != magic)
    {
        cprintf(COLOR_RED, "Error: Magic number %#x is invalid!\n", magic);
        logf(error, "Invalid magic number: %#x \n", magic);
        for (;;);
    }

    if (mbd->flags & MULTIBOOT_INFO_MEMORY)
    {
        printf("mem_lower = %i KB, mem_upper = %i KB\n", mbd->mem_lower, mbd->mem_upper);
    }

    if (mbd->flags & MULTIBOOT_INFO_MEM_MAP)
    {
        printf("mmap_addr: %#x, mmap_length: %#x\n", mbd->mmap_addr, mbd->mmap_length);

        for (multiboot_memory_map_t* map = (multiboot_memory_map_t*) mbd->mmap_addr; 
            (uint32_t) map < mbd->mmap_addr + mbd->mmap_length;
            map = (multiboot_memory_map_t*) ((uint32_t) map + map->size + sizeof(map->size)))
        {
            if (map->type > 5)
            {
                map->type = 6;
            }
            printf("[base_addr_high = %#x, base_addr_low = %#x\nlength_high = %#x, length_low = %#x, type = %#x (%s)]\n", map->base_addr_high, map->base_addr_low, map->length_high, map->length_low, map->type, mem_type[map->type - 1]);
        }
    }

    init_dt();
    init_timer(100);

    init_pmm(mbd->mem_upper);
    init_vmm();
    uint32_t i = mbd->mmap_addr;
    while (i < mbd->mmap_addr + mbd->mmap_length)
    {
        multiboot_memory_map_t* me = (multiboot_memory_map_t*) i;
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
}