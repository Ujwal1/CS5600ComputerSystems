/*
 * pm_heap.c
 *
 *  Created on: Feb 28, 2023
 *      Author: ujwal
 */


#include "pm_heap.h"
#include <stdint.h>
#include <pthread.h>

char pm_heap[PM_HEAP_SIZE];

typedef struct {
    void* ptr;
    size_t size;
    int free;
} pm_block_t;

#define MAX_BLOCKS (PM_HEAP_SIZE / sizeof(pm_block_t))
static pm_block_t pm_blocks[MAX_BLOCKS];
static size_t pm_num_blocks = 0;

static pthread_mutex_t pm_mutex = PTHREAD_MUTEX_INITIALIZER;

void pm_heap_init(void)
{
//	char pm_heap[PM_HEAP_SIZE];
    pm_blocks[0].ptr = pm_heap;
    pm_blocks[0].size = PM_HEAP_SIZE;
    pm_blocks[0].free = 1;
    pm_num_blocks = 1;
}

void* pm_malloc(size_t size)
{
	void* ptr = NULL;

	pthread_mutex_lock(&pm_mutex);
    // find a free block with enough space
    for (size_t i = 0; i < pm_num_blocks; i++) {
        if (pm_blocks[i].free && pm_blocks[i].size >= size) {
            pm_blocks[i].free = 0;
            if (pm_blocks[i].size > size) {
                // split the block
                pm_block_t* new_block = &pm_blocks[pm_num_blocks++];
                new_block->ptr = (char*)pm_blocks[i].ptr + size;
                new_block->size = pm_blocks[i].size - size;
                new_block->free = 1;
                pm_blocks[i].size = size;
            }
            ptr =  pm_blocks[i].ptr;
            break;
        }
    }
    pthread_mutex_unlock(&pm_mutex);

    // no free block with enough space
    return ptr;
}

void pm_free(void* ptr)
{
	pthread_mutex_lock(&pm_mutex);
    // find the block corresponding to ptr
    for (size_t i = 0; i < pm_num_blocks; i++) {
        if (pm_blocks[i].ptr == ptr) {
            pm_blocks[i].free = 1;
            // coalesce with adjacent free blocks
            while (i > 0 && pm_blocks[i-1].free) {
                pm_blocks[i-1].size += pm_blocks[i].size;
                for (size_t j = i; j < pm_num_blocks - 1; j++) {
                    pm_blocks[j] = pm_blocks[j+1];
                }
                pm_num_blocks--;
                i--;
            }
            while (i < pm_num_blocks - 1 && pm_blocks[i+1].free) {
                pm_blocks[i].size += pm_blocks[i+1].size;
                for (size_t j = i+1; j < pm_num_blocks - 1; j++) {
                    pm_blocks[j] = pm_blocks[j+1];
                }
                pm_num_blocks--;
            }
            break;
        }
    }
    pthread_mutex_unlock(&pm_mutex);
}
