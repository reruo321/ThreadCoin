#ifndef __TC_STDIO__
#define __TC_STDIO__
#include <stdio.h>
#endif

#ifndef __TC_PTHREAD__
#define __TC_PTHREAD__
#include <pthread.h>
#endif

#define QUEUE_MAX_SIZE 10000

typedef struct{
	pthread_t tid[QUEUE_MAX_SIZE];
	int is_running[QUEUE_MAX_SIZE];
	int front;
	int back;
} Queue;

void queue_init(Queue *q);
int queue_isempty(Queue *q);
int queue_isfull(Queue *q);
void enqueue(Queue *q);
void dequeue(Queue *q);
int queue_front(Queue *q);
