/*
 * queue.c
 *
 *  Created on: Jan 24, 2023
 *      Author: ujwal
 */
#include "queue.h"
#include<stdlib.h>

// the function to put an element in a queue
void enqueue(queue_t *queue, void *element) {
	queue_t *newNode = (queue_t*) malloc(sizeof(queue_t));
	newNode->data = element;
	newNode->next = NULL;

	//finding last node in queue
	queue_t *last = queue;
	while (last->next != NULL) {
		last = last->next;
	}

	last->next = newNode;
	newNode->prev = last;
}

// function to remove an elemnt from a queue
void* dequeue(queue_t *queue) {
	if (queue->next == NULL) {
		return NULL;
	}
	void *data = queue->next->data;

	//removing the first node from the queue
	queue_t *front = queue->next;
	queue->next = front->next;
	if (front->next != NULL) {
		front->next->prev = queue;
	}
	free(front);

	return data;
}

// function to dequeue a process from the queue with highest priority
process_t* dequeueProcess(queue_t *queue) {
	process_t *highestPriorityProcess = NULL;
	queue_t *current = queue->next;
	while (current != NULL) {
		process_t *currentProcess = (process_t*) current->data;
		if (highestPriorityProcess == NULL
				|| currentProcess->priority
						> highestPriorityProcess->priority) {
			highestPriorityProcess = currentProcess;
		}
		current = current->next;
	}

	//remove the process from the queue
	current = queue->next;
	while (current != NULL) {
		if (current->data == highestPriorityProcess) {
			current->prev->next = current->next;
			if (current->next != NULL) {
				current->next->prev = current->prev;
			}
			free(current);
			break;
		}
		current = current->next;
	}
	return highestPriorityProcess;
}

//function to find the size of the queue
int qsize(queue_t *queue) {
	int size = 0;
	queue_t *current = queue->next;
	while (current != NULL) {
		size++;
		current = current->next;
	}
	return size;
}
