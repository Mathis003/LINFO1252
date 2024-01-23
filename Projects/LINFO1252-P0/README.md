# Dynamic Memory Allocation Project

## Introduction

This project implements custom `malloc` and `free` functions for dynamic memory allocation, following the guidelines of LINFO1252 - Systèmes Informatiques course.

## Specifications

- `void init()`: Initializes memory space.
- `void *my_malloc(size_t size)`: Allocates memory of at least `size` bytes.
- `void my_free(void *ptr)`: Frees allocated memory.

## Implementation

- The `init` function initializes memory with custom metadata.
- Custom metadata includes the next-fit offset and block size information.
- `merge_next_free_blocks` combines adjacent (to the right) free memory blocks.
- `initialize_allocated_block` initializes new allocated blocks.
- The algorithm employs a next-fit strategy for allocation.