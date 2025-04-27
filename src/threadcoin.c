#ifndef __TC_THREAD_COIN__
#define __TC_THREAD_COIN__
#include "threadcoin.h"
#endif

#ifndef __TC_QUEUE__
#define __TC_QUEUE__
#include "queue.h"
#endif

int coin;
Queue q;
pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;
const char * prompt_name;

Command commands[] = {
	{"show", (void (*)(void *))tc_show, 0},
	{"add", (void (*)(void *))tc_add, 0},
	{"del", (void (*)(void *))tc_del, 0},
	{"exit", (void (*)(void *))tc_exit, 0},
	{NULL, NULL, 0},
};

void __tc_init(){
	coin = 0;
	queue_init(&q);
	enqueue(&q);
}

void tc_print_prompt(){
	printf("%s>>", prompt_name);
}

void tc_read_command_line(char * line){
	size_t len = strlen(line);
	if(len == 0)
		return;
	if(line[len-1] == '\n')
		line[len-1] = '\0';
	
	char * cmd = strtok(line, " ");
	if(cmd == NULL || strlen(cmd) == 0)
		return;
	
	for(int i=0; commands[i].name != NULL; ++i){
		if(strcmp(cmd, commands[i].name) == 0){
			commands[i].func(line);
			return;
		}
	}
	printf("ERROR: Invalid Command!\n");
	printf("Please type one of these: show, add, del, exit\n");
}

void tc_show(){
	printf("The current number of coins: %d\n", coin);
}

void tc_add(){
	enqueue(&q);
}

void tc_del(){
	dequeue(&q);
}

void tc_exit(){
	__tc_exit();
	exit(0);
}

void __tc_exit(){
	
	for(int i=q.front; i<q.back; ++i){
		q.is_running[i] = 0;
	}

	while(!queue_isempty(&q)){
		if(q.tid[q.front] != 0){
			if(pthread_cancel(q.tid[q.front]) != 0){
				fprintf(stderr, "ERROR: Failed to join thread\n");
			}
		}
		++q.front;
	}
	for(int i=0; i<q.back; ++i){
		pthread_join(q.tid[i], NULL);
	}

	pthread_mutex_destroy(&mlock);
}

void* pthread_get_coin(void* arg){
	int ir = *(int *)arg;
	while(ir){
		pthread_mutex_lock(&mlock);
		if(!ir){
			pthread_mutex_unlock(&mlock);
			break;
		}
		++coin;
		pthread_mutex_unlock(&mlock);
		usleep(COIN_USLEEP_TIME);
	}
	return NULL;
}
