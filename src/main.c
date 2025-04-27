#ifndef __TC_STDIO__
#define __TC_STDIO__
#include <stdio.h>
#endif

#ifndef __TC_STDLIB__
#define __TC_STDLIB__
#include <stdlib.h>
#endif

#ifndef __TC_THREAD_COIN__
#define __TC_THREAD_COIN__
#include "threadcoin.h"
#endif

#ifndef __TC_QUEUE__
#define __TC_QUEUE__
#include "queue.h"
#endif

#define MAX_LINE_LEN 1000

char * line;

int main(){
	line = malloc(MAX_LINE_LEN * sizeof(char));
	if(line == NULL){
		fprintf(stderr, "ERROR: Failed to allocate memory\n");
		return 1;
	}

	__tc_init();
	prompt_name = "reruo";

	while(1){
		tc_print_prompt();
		if(fgets(line, MAX_LINE_LEN, stdin) == NULL){
			if(feof(stdin)){
				printf("EOF received. Bye bye!\n");
				tc_exit();
			} else{
				fprintf(stderr, "ERROR: Failed to read input\n");
				free(line);
				return 1;
			}
		}
		tc_read_command_line(line);
	}
	free(line);
	return 0;
}
