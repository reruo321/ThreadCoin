#ifndef __TC_STDIO__
#define __TC_STDIO__
#include <stdio.h>
#endif

#ifndef __TC_UNISTD__
#define __TC_UNISTD__
#include <unistd.h>
#endif

#ifndef __TC_STDLIB__
#define __TC_STDLIB__
#include <stdlib.h>
#endif

#ifndef __TC_STRING__
#define __TC_STRING__
#include <string.h>
#endif

extern const char * prompt_name;

#define COIN_USLEEP_TIME 100000

typedef struct{
	const char *name;
	void (*func)(void *);
	int argc;
} Command;

void __tc_init(void);
void __tc_exit(void);

void tc_print_prompt(void);
void tc_read_command_line(char * line);

void tc_show(void);
void tc_add(void);
void tc_del(void);
void tc_exit(void);

void* pthread_get_coin(void* arg);
