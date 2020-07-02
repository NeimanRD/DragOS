#ifndef PHYSMM_H
#define PHYSMM_H

#include <stdint.h>
#include <stddef.h>

//! 8 blocks per byte
#define PMMNGR_BLOCKS_PER_BYTE 8
 
//! block size (4k)
#define PMMNGR_BLOCK_SIZE	4096
 
//! block alignment
#define PMMNGR_BLOCK_ALIGN	PMMNGR_BLOCK_SIZE

typedef	uint32_t physical_addr;

int mmap_first_free();
void pmmngr_init(size_t memSize, physical_addr bitmap);
void pmmngr_init_region(physical_addr base, size_t size);
void pmmngr_deinit_region(physical_addr base, size_t size);
void* pmmngr_alloc_block();
void pmmngr_free_block(void* p);
void* pmmngr_alloc_blocks(size_t size);
void pmmngr_free_blocks(void* p, size_t size);


#endif