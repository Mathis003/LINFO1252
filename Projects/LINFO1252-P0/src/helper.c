#include "../headers/helper.h"


uint16_t merge_next_free_blocks(uint16_t *my_heap, uint16_t loc)
{
    uint16_t available_size = my_heap[loc];
    uint16_t next_loc = loc + (available_size + SIZE_HEADER) / 2;
    uint16_t new_size_block;

    while ((next_loc <= (HEAP_SIZE - 2 * SIZE_HEADER) / 2) &&  // The next block is available in the heap
            !(my_heap[next_loc] & 0x1))                        // The next block is free
    {
        // Add the size of the next block to the current block
        new_size_block = my_heap[next_loc];
        next_loc +=  (new_size_block + SIZE_HEADER) / 2;
        available_size += new_size_block + SIZE_HEADER;
    }

    // Update the new size of the new merged block
    uint16_t merged_size = available_size;
    my_heap[loc] = merged_size;
    return merged_size;
}


void initialize_allocated_block(uint16_t *my_heap, uint16_t loc, uint16_t available_size, uint16_t size)
{
    uint16_t next_loc = loc + (size + SIZE_HEADER) / 2;

    // Special case: If the block is the last one (with no header after it) (special case)
    if (next_loc == HEAP_SIZE / 2)
    {
        my_heap[loc] = size;
        my_heap[0] = 1;
    }

    // General case: If the block is not the last one and are available in the heap
    else
    {
        // If the block is big enough to allocate the requested size + 2 bytes for the header + the remaining size (minimal 2 bytes)
        if (size <= available_size - 2 * SIZE_HEADER)
        {
            uint16_t leftovers = available_size - (size + SIZE_HEADER);
            my_heap[loc] = size;
            my_heap[next_loc] = leftovers;
            my_heap[0] = next_loc;
        }
        
        // Allocate the whole block
        else 
        {
            my_heap[loc] = available_size;
            my_heap[0] = loc + (available_size + SIZE_HEADER) / 2;
        }
    }

    my_heap[loc] += 0x1;  // Mark the block as allocated
}


void looped(uint16_t *loc, uint8_t *has_looped)
{
    if (*loc >= HEAP_SIZE / 2 && !(*has_looped))
    {
        *has_looped = 1;
        *loc = 1;
    }
}