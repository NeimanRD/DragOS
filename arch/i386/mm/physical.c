#include <mm/physical.h>
#include <lib/string.h>
#include <stdbool.h>

static uint32_t	mm_memory_size = 0;
static uint32_t	mm_used_blocks = 0;
static uint32_t	mm_max_blocks = 0;
static uint32_t* mm_memory_map = 0;

static size_t pmmngr_get_memory_size();
static uint32_t pmmngr_get_block_count();
static uint32_t pmmngr_get_use_block_count();
static uint32_t pmmngr_get_free_block_count();
static uint32_t pmmngr_get_block_size();

static inline void mmap_set(int bit) 
{
  mm_memory_map[bit / 32] |= (1 << (bit % 32));
}

static inline void mmap_unset(int bit) 
{
  mm_memory_map[bit / 32] &= ~ (1 << (bit % 32));
}

static inline bool mmap_test(int bit) 
{
 return mm_memory_map[bit / 32] &  (1 << (bit % 32));
}

int mmap_first_free()
{
    // find the first free bit
	for (uint32_t i = 0; i < pmmngr_get_block_count() / 32; i++)
		if (mm_memory_map[i] != 0xffffffff)
        {
			for (int j=0; j<32; j++) 
            {		// test each bit in the dword
				int bit = 1 << j;
				if (!(mm_memory_map[i] & bit))
                {
					return i*4*8+j;
                }
			}
        }
 
	return -1;
}

int mmap_first_free_s (size_t size) 
{
	if (size==0)
		return -1;

	if (size==1)
		return mmap_first_free ();

	for (uint32_t i=0; i<pmmngr_get_block_count() /32; i++)
		if (mm_memory_map[i] != 0xffffffff)
			for (int j=0; j<32; j++) {	//! test each bit in the dword

				int bit = 1<<j;
				if (! (mm_memory_map[i] & bit) ) {

					int startingBit = i*32;
					startingBit+=bit;		//get the free bit in the dword at index i

					uint32_t free=0; //loop through each bit to see if its enough space
					for (uint32_t count=0; count<=size;count++) {

						if (! mmap_test (startingBit+count) )
							free++;	// this bit is clear (free frame)

						if (free==size)
							return i*4*8+j; //free count==size needed; return index
					}
				}
			}

	return -1;
}


void pmmngr_init(size_t memSize, physical_addr bitmap) {
 
	mm_memory_size	=	memSize;
	mm_memory_map	=	(uint32_t*) bitmap;
	mm_max_blocks	=	(pmmngr_get_memory_size()*1024) / PMMNGR_BLOCK_SIZE;
	mm_used_blocks	=	pmmngr_get_block_count();
 
	//! By default, all of memory is in use
	memset(mm_memory_map, 0xf, pmmngr_get_block_count() / PMMNGR_BLOCKS_PER_BYTE );
}

void pmmngr_init_region(physical_addr base, size_t size)
{
	int align = base / PMMNGR_BLOCK_SIZE;
	int blocks = size / PMMNGR_BLOCK_SIZE;
 
	for (; blocks>0; blocks--) {
		mmap_unset (align++);
		mm_used_blocks--;
	}
 
	mmap_set (0);	//first block is always set. This insures allocs cant be 0
}

void pmmngr_deinit_region (physical_addr base, size_t size) 
{ 
	int align = base / PMMNGR_BLOCK_SIZE;
	int blocks = size / PMMNGR_BLOCK_SIZE;
 
	for (; blocks>0; blocks--) {
		mmap_set (align++);
		mm_used_blocks++;
	}
}

void* pmmngr_alloc_block() 
{
 
	if (pmmngr_get_free_block_count() <= 0)
		return 0;	//out of memory
 
	int frame = mmap_first_free ();
 
	if (frame == -1)
		return 0;	//out of memory
 
	mmap_set (frame);
 
	physical_addr addr = frame * PMMNGR_BLOCK_SIZE;
	mm_used_blocks++;
 
	return (void*)addr;
}

void pmmngr_free_block(void* p) 
{
	physical_addr addr = (physical_addr) p;
	int frame = addr / PMMNGR_BLOCK_SIZE;
 
	mmap_unset(frame);
 
	mm_used_blocks--;
}

void* pmmngr_alloc_blocks(size_t size) 
{
	if (pmmngr_get_free_block_count() <= size)
		return 0;	//not enough space

	int frame = mmap_first_free_s(size);

	if (frame == -1)
		return 0;	//not enough space

	for (uint32_t i=0; i<size; i++)
		mmap_set(frame+i);

	physical_addr addr = frame * PMMNGR_BLOCK_SIZE;
	mm_used_blocks += size;

	return (void*) addr;
}

void pmmngr_free_blocks(void* p, size_t size) 
{
	physical_addr addr = (physical_addr) p;
	int frame = addr / PMMNGR_BLOCK_SIZE;

	for (uint32_t i=0; i<size; i++)
		mmap_unset(frame+i);

	mm_used_blocks -= size;
}

static size_t pmmngr_get_memory_size() 
{
	return mm_memory_size;
}

static uint32_t pmmngr_get_block_count() 
{
	return mm_max_blocks;
}

static uint32_t pmmngr_get_use_block_count()
{
	return mm_used_blocks;
}

static uint32_t pmmngr_get_free_block_count() 
{
	return mm_max_blocks - mm_used_blocks;
}

static uint32_t pmmngr_get_block_size() 
{
	return PMMNGR_BLOCK_SIZE;
}