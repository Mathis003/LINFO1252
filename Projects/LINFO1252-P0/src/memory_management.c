#include "../headers/memory_management.h"

void init()
{
    uint16_t *my_heap = (uint16_t *) MY_HEAP;

    my_heap[0] = 1;                            // nextfit offset
    my_heap[1] = HEAP_SIZE - 2 * SIZE_HEADER;  // size of the first free block
}


void *my_malloc(size_t size)
{
    // Check the validity of the arguments
    if ((size > HEAP_SIZE - 2 * SIZE_HEADER) || (size <= 0)) return NULL;

    uint16_t *my_heap = (uint16_t *) MY_HEAP;

    // If size is uneven, add 1
    if (size & 0x1) size++;

    uint16_t initial_loc = my_heap[0];
    uint16_t loc = initial_loc;

    uint16_t available_size;
    uint8_t has_looped = 0;

    while (((loc < HEAP_SIZE / 2) && !has_looped) ||  // If we haven't reached the end of the heap and we haven't looped
            (has_looped && (loc <= initial_loc)))     // If we have looped and we haven't reached the initial loc
    {
        // If the block is allocated, go to the next one
        if (my_heap[loc] & 0x1) loc += (my_heap[loc] - 0x1 + SIZE_HEADER) / 2;

        // If the block is free, check if we can merge it with the next ones and then check if we can allocate it
        else
        {
            available_size = merge_next_free_blocks(my_heap, loc);
            if (size <= available_size)
            {
                initialize_allocated_block(my_heap, loc, available_size, size);
                return (void *) (MY_HEAP + 2 * loc + SIZE_HEADER);
            } else loc += (available_size + SIZE_HEADER) / 2;
        }

        // If we reached the end of the heap, start from the beginning
        looped(&loc, &has_looped);
    }

    // If we haven't found any free block, return NULL
    return NULL;
}


void my_free(void *pointer)
{
    // Check the validity of the argument
    if (pointer == NULL) return;
    
    uint16_t *header_block = (uint16_t *) pointer - SIZE_HEADER / 2;

    if (header_block == NULL) return;
    
    uint16_t *my_heap = (uint16_t *) MY_HEAP;

    *header_block &= 0xFFFE; // Mark the block as free

    uint16_t loc = header_block - my_heap;
    merge_next_free_blocks(my_heap, loc);

    // If the nextfit offset is in the middle of the merged blocks, update it at the beginning of the merged blocks
    if ((loc < my_heap[0]) && my_heap[0] <= loc + my_heap[loc] / 2) my_heap[0] = loc;

    pointer = NULL;
}