#ifndef HELPER_H
#define HELPER_H

#include "var.h"

/*
* Merge the current free block with next blocks if they are availables in the heap and free.
*
* @param my_heap:          pointer to the heap (uint16_t array)
* @param loc:              location of the current free block (index in the heap)
* @param available_size:   pointer to the size of the current free block
* @return:                 the size of the new merged free block
*/
uint16_t merge_next_free_blocks(uint16_t *my_heap, uint16_t loc);

/*
* Initialize an allocated block.
*
* @param my_heap:          pointer to the heap (uint16_t array)
* @param loc:              location of the free block (index in the heap)
* @param available_size:   size of the free block
* @param size:             size requested by the user for the allocatation
* @return:                 1 if the block has been allocated, 0 otherwise
*/
void initialize_allocated_block(uint16_t *my_heap, uint16_t loc, uint16_t available_size, uint16_t size);


/*
* If we reached the end of the heap, start from the beginning.
*
* @param loc:           pointer to the location of the current block (index in the heap)
* @param has_looped:    pointer to a boolean indicating if we have already looped
* @return:              void
*/
void looped(uint16_t *loc, uint8_t *has_looped);

#endif /* HELPER_H */