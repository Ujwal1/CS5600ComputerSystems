/*
 * pm_heap.h
 *
 *  Created on: Feb 28, 2023
 *      Author: ujwal
 */

#ifndef PM_HEAP_H
#define PM_HEAP_H

#include <stddef.h>

#define PM_HEAP_SIZE (10 * 1024 * 1024) // 10MB
extern char pm_heap[PM_HEAP_SIZE];

void pm_heap_init(void);
void* pm_malloc(size_t size);
void pm_free(void* ptr);

#endif
