#include <stdio.h>
#include <stdint.h>
#include <assert.h>

const uint16_t HEAP_SIZE = 64000;
const uint8_t SIZE_HEADER = 2;

uint8_t MY_HEAP[64000];


void init()
{
    uint16_t *my_heap = (uint16_t *) MY_HEAP;

    my_heap[0] = 1;                            // nextfit offset
    my_heap[1] = HEAP_SIZE - 2 * SIZE_HEADER;  // size of the first free block
}


/*
* Merge the current free block with next blocks if they are availables in the heap and free.
* @param my_heap:          pointer to the heap (uint16_t array)
* @param loc:              location of the current free block (index in the heap)
* @param available_size:   pointer to the size of the current free block
* @return:                 the size of the new merged free block
*/
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


/*
* Initialize an allocated block.
* @param my_heap:          pointer to the heap (uint16_t array)
* @param loc:              location of the free block (index in the heap)
* @param available_size:   size of the free block
* @param size:             size requested by the user for the allocatation
* @return:                 1 if the block has been allocated, 0 otherwise
*/
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


/*
* If we reached the end of the heap, start from the beginning.
* @param loc:           pointer to the location of the current block (index in the heap)
* @param has_looped:    pointer to a boolean indicating if we have already looped
* @return:              void
*/
void looped(uint16_t *loc, uint8_t *has_looped)
{
    if (*loc >= HEAP_SIZE / 2 && !(*has_looped))
    {
        *has_looped = 1;
        *loc = 1;
    }
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



void print_HEAP()
{
    printf("==== PRINT THE HEAP ====\n");

    uint16_t loc = 2;
    uint16_t size;

    printf("nextfit offset\t");
    printf("adress: %d\t", 0);
    printf("size: %d \t", 2);
    printf("value: %d\n", 2 * ((MY_HEAP[0] & 0xFF) + (MY_HEAP[1] << 8)));

    while (loc < HEAP_SIZE)
    {
        size = (MY_HEAP[loc] & 0xFE) + (MY_HEAP[loc + 1] << 8);

        if (!(MY_HEAP[loc] & 0x1)) printf("free    \t");
        else printf("allocated\t");

        printf("adress: %d\t", loc);
        printf("size: %d \t", size);
        printf("value: [ ");

        if (!(MY_HEAP[loc] & 0x1)) printf("... ");
        else
        {
            uint16_t zero_counter = 0;
            for (uint16_t i = loc + SIZE_HEADER; i < loc + size + SIZE_HEADER; i++)
            {
                if (MY_HEAP[i] == 0) zero_counter++;                
                else
                {
                    if (zero_counter > 0) printf("0*%d ", zero_counter);
                    zero_counter = 0;
                    printf("%x ", MY_HEAP[i]);
                }
            }
            if (zero_counter > 0) printf("0*%d ", zero_counter);
        }
        printf("]\n");
        loc += size + SIZE_HEADER;
    }
    printf("\n");
}


int main(int argc, char *argv[])
{
    //** Empty HEAP **//
    printf("Empty HEAP:\n");
    init();
    print_HEAP();

    //** Invalid Argument Malloc **//
    printf("Invalid Argument Malloc:\n");
    void *invalid_malloc1 = my_malloc(0);
    void *invalid_malloc2 = my_malloc(-2);
    void *invalid_malloc3 = my_malloc(64000);
    void *invalid_malloc4 = my_malloc(63999);
    if (invalid_malloc1 != NULL) printf("Error!");
    if (invalid_malloc2 != NULL) printf("Error!");
    if (invalid_malloc3 != NULL) printf("Error!");
    if (invalid_malloc4 != NULL) printf("Error!");
    print_HEAP();


    //** Simple Malloc **//
    printf("Simple Malloc:\n");
    uint8_t *simple_malloc = (uint8_t *) my_malloc(4);
    if (simple_malloc == NULL) printf("Error: malloc return NULL\n");
    *simple_malloc = 130;
    if (*simple_malloc != 130) printf("Error: the value is not the expected one\n");
    print_HEAP();
    

    void *other_malloc = my_malloc(100);

    print_HEAP();

    //** Simple Free **//
    printf("Simple Free:\n");
    my_free(simple_malloc);
    print_HEAP();

    //** Free With Merged Next Block (Only One) **//
    printf("Free With Merged Next Block (Only One):\n");
    my_free(other_malloc);
    print_HEAP();

    init();

    //** Multiple Big Malloc **//
    printf("Multiple Big Malloc:\n");
    void *big_malloc1 = my_malloc(20000);
    void *big_malloc2 = my_malloc(10000);
    void *big_malloc3 = my_malloc(10000);
    void *big_malloc4 = my_malloc(20000);
    void *big_malloc5 = my_malloc(3988);
    print_HEAP();


    //** HEAP Full **//
    printf("HEAP Full:\n");
    void *full_malloc1 = my_malloc(20000);
    void *full_malloc2 = my_malloc(1);
    void *full_malloc3 = my_malloc(0);
    void *full_malloc4 = my_malloc(-2);
    if (full_malloc1 != NULL) printf("Error!");
    if (full_malloc2 != NULL) printf("Error!");
    if (full_malloc3 != NULL) printf("Error!");
    if (full_malloc4 != NULL) printf("Error!");
    print_HEAP();


    //** Free With Merged Next Block (Multiple) **//
    printf("Free With Merged Next Block (Multiple):\n");
    my_free(big_malloc3);
    my_free(big_malloc4);
    print_HEAP();
    my_free(big_malloc2);
    print_HEAP();


    init();
    void *first = my_malloc(10000);
    void *second = my_malloc(20000);
    void *third = my_malloc(15000);
    void *fourth = my_malloc(4);
    void *fifth = my_malloc(10);
    void *sixth = my_malloc(12);
    void *seventh = my_malloc(52);
    void *eight = my_malloc(10000);
    void *ninth = my_malloc(10000);
    void *ten = my_malloc(8902);
    my_free(fourth);
    my_free(fifth);
    my_free(sixth);
    my_free(seventh);


    //** Malloc but no available size **//
    printf("Malloc but no available size\n");
    print_HEAP();
    void *no_size = my_malloc(52 + 12 + 10 + 4 + 8);
    if (no_size != NULL) printf("Error!\n");
    print_HEAP();


    init();
    void *un = my_malloc(10000);
    void *deux = my_malloc(20000);
    void *trois = my_malloc(15000);
    void *quatres = my_malloc(4);
    void *cinq = my_malloc(10);
    void *six = my_malloc(12);
    void *sept = my_malloc(52);
    void *huit = my_malloc(10000);
    void *neuf = my_malloc(10000);
    void *dix = my_malloc(8902);
    my_free(quatres);
    my_free(cinq);
    my_free(six);
    my_free(sept);

    //** Malloc but available size if merged 4 blocks **//
    printf("Malloc but available size if merged 4 blocks\n");
    print_HEAP();
    my_malloc(84);
    print_HEAP();
}