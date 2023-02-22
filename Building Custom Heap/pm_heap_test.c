/*
 * pm_heap_test.c
 *
 *  Created on: Feb 21, 2023
 *      Author: ujwal
 */

#include <stdio.h>
#include "pm_heap.h"

int main() {
    pm_heap_init();

    void *ptr1 = pm_malloc(16);
    if (ptr1 == NULL) {
        printf("Failed to allocate memory!\n");
        return 1;
    }

    void *ptr2 = pm_malloc(32);
    if (ptr2 == NULL) {
        printf("Failed to allocate memory!\n");
        return 1;
    }

    void *ptr3 = pm_malloc(64);
    if (ptr3 == NULL) {
        printf("Failed to allocate memory!\n");
        return 1;
    }

    pm_free(ptr2);

    void *ptr4 = pm_malloc(128);
    if (ptr4 == NULL) {
        printf("Failed to allocate memory!\n");
        return 1;
    }

    // Uncomment this part of code to see an allocation fail.
	//    void *ptr5 = pm_malloc(128000000);
	//        if (ptr5 == NULL) {
	//            printf("Failed to allocate memory!\n");
	//            return 1;
	//        }

    pm_free(ptr1);
    pm_free(ptr3);
    pm_free(ptr4);

    printf("pm_heap test successful!\n");

    return 0;
}
