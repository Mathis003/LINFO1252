#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include "helper.h"

/*
* Initialize the heap with a two metadata :
* - The first one is the nextfit offset (index in the heap)
* - The second one is the size of the first free block
*
* @param: void
* @return: void
*/
void init();

void *my_malloc(size_t size);

void my_free(void *pointer);

#endif /* MEMORY_MANAGEMENT_H */