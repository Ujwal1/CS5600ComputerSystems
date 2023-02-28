/*
 * pm_heap_test.c
 *
 *  Created on: Feb 28, 2023
 *      Author: ujwal
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "pm_heap.h"

#define NUM_THREADS 10
#define ALLOC_SIZE 1000
#define NUM_ALLOCS 100

void* thread_func()
{
    // Allocate and free memory repeatedly
    for (int i = 0; i < NUM_ALLOCS; i++) {
        void* ptr = pm_malloc(ALLOC_SIZE);
        if (ptr == NULL) {
            printf("Failed to allocate memory!\n");
            exit(1);
        }
        pm_free(ptr);
    }

    return NULL;
}

int main() {
    pm_heap_init();

    // Create multiple threads
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, thread_func, NULL) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    printf("pm_heap test successful!\n");

    return 0;
}
