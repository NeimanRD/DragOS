#ifndef PHYSICAL_H
#define PHYSICAL_H

#include <stdint.h>

uint32_t pmm_alloc_page();
void init_pmm(uint32_t start);
void pmm_free_page(uint32_t p);

extern char pmm_paging_active;

#define PMM_STACK_ADDR 0xFF000000

#endif