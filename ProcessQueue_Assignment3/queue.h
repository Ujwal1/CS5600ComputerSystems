/*
 * queue.h
 *
 *  Created on: Jan 24, 2023
 *      Author: ujwal
 */

#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct {
	int id;
	char *name;
	int priority;
} process_t;

typedef struct queue_t {
	void *data;
	struct queue_t *next;
	struct queue_t *prev;
} queue_t;

void enqueue(queue_t *queue, void *element);
void* dequeue(queue_t *queue);
process_t* dequeueProcess(queue_t *queue);
int qsize(queue_t *queue);

#endif /* QUEUE_H_ */
