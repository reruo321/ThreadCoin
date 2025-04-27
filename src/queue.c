#ifndef __TC_PTHREAD__
#define __TC_PTHREAD__
#include <pthread.h>
#endif

#ifndef __TC_QUEUE__
#define __TC_QUEUE__
#include "queue.h"
#endif

#ifndef __TC_THREAD_COIN__
#define __TC_THREAD_COIN__
#include "threadcoin.h"
#endif

void queue_init(Queue *q){
	q->front = 0;
	q->back = 0;
	for(int i=0; i<QUEUE_MAX_SIZE; ++i){
		q->is_running[i] = 0;
	}
}

int queue_isempty(Queue *q){
	return (q->front == q->back);
}

int queue_isfull(Queue *q){
	return (q->back == QUEUE_MAX_SIZE);
}

void enqueue(Queue *q){
	if(!queue_isfull(q)){
		q->is_running[q->back] = 1;
		if(pthread_create(&(q->tid[q->back]), NULL, pthread_get_coin, &(q->is_running[q->back])) != 0){
			fprintf(stderr, "ERROR: Failed to create thread\n");
			q->is_running[q->back] = 0;
			return;
		}
		++(q->back);
	}
	else
		printf("ERROR: thread queue is full\n");
}

void dequeue(Queue *q){
	if(!queue_isempty(q)){
		q->is_running[q->front] = 0;
		if(pthread_cancel(q->tid[q->front]) != 0){
			fprintf(stderr, "ERROR: Failed to join thread\n");
		}
		++(q->front);
	}
	else
		printf("ERROR: no thread is running\n");
}

int queue_front(Queue *q){
	if(!queue_isempty(q)){
		return q->front;
	}
	printf("ERROR: no thread is running\n");
	return -1;
}
