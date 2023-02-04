/*
 * GuptaU.CS5600.S23.c
 *
 *  Created on: Jan 31, 2023
 *      Author: ujwal
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define ARR_SIZE 10
int shared_array[10] = {0};

void *worker(void *data) {
	char *name = (char*)data;
	pthread_t thread_id = pthread_self();

	for (int i = 0; i < 120; i++) {
		usleep(50000);
		printf("Hi from thread name = %s and thread_id:%lu\n", name, thread_id);
	}
	printf("Thread %s with thread_id: %lu done!\n", name, thread_id);
	return NULL;
}

void *worker_write(void* data) {
	char *name = (char*)data;
	for (int i = 0; i < ARR_SIZE; i++) {
		usleep(10000);
		shared_array[i] = i+10;
		printf("Thread %s writing to shared_array[%d] = %d \n", name, i, shared_array[i]);
	}
	return NULL;
}

void *worker_read(void* data) {
	char *name = (char*)data;
	for (int i = 0; i < ARR_SIZE; i++) {
		usleep(10000);
		printf("Thread %s reading from shared_array[%d] = %d \n", name, i, shared_array[i]);
	}
	return NULL;
}

int main(void) {
	pthread_t th1, th2;
	pthread_create(&th1, NULL, worker, "X");
	pthread_create(&th2, NULL, worker, "Y");
	sleep(1);
	printf("====> Cancelling Thread Y with thread_id: %lu!!\n", (unsigned long) th2);
	pthread_cancel(th2);
	usleep(100000);
	printf("====> Cancelling Thread X with thread_id: %lu!!\n", (unsigned long) th1);
	pthread_cancel(th1);


	printf("\n\nDemo for shared memory usage with one process with 'write' rights and other with just 'read'.\n\n");
	pthread_create(&th1, NULL, worker_write, "X");
	pthread_create(&th2, NULL, worker_read, "Y");
	sleep(1);
	printf("====> Cancelling Thread Y with thread_id: %lu!!\n", (unsigned long) th2);
	pthread_cancel(th2);
	usleep(100000);
	printf("====> Cancelling Thread X with thread_id: %lu!!\n\n", (unsigned long) th1);
	pthread_cancel(th1);


	for (int i = 0; i < ARR_SIZE; i++) {
			printf("Reading from shared_array[%d] = %d \n", i, shared_array[i]);
		}

	printf("Exiting from main program\n");
	return 0;
}

/**
 * 3.
 * Yes, the threads are able to communicate by means of sharing the same data. In my example,
 * I have taken a global array and using a thread to load data into it and other thread that just reads the data.
 *
 * The array is of size 10. A[0..9] with A[i] = i+10;
 *
 * 4.
 * The shared array that we have is consistent ie: it holds the data that is being written to it
 * by process X. This is expected behaviour as only thread X has write priviliges to it.
 *
 * Before the data is written to the shared memory, the whole array is initialised with values 0.
 * The behavour of two threads that read and write data from the shared_array, is not consistent at each run.
 * In some runs, the thread Y reads the data after updation by the thread X for some indexex i for shared_array[i],
 * while in some runs the thread Y reads the shared_array[i] as 0 as it hasn't been updated by thread X yet.
 *
 * Thus this problem of inconsistent read by thread Y because thread X is in the middle of updating it results
 * in incorrect data being displayed or used in the program. To avoid this, a mutex lock should be used to
 * ensure that only one thread can access shared data at a time. *
 *
 */
