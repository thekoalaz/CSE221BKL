#include "./cpu_test.h"

data_t cpu_process_creation(data_t overhead) {
	unsigned start, end;
	pid_t childPID;
	int i, status = 0;
	data_t total = 0;

	for(i=0 ; i < TASK_CREATION_NUM ; ++i){
		start = ccnt_read();
		childPID = fork();
		end = ccnt_read();
		
		if(childPID < 0) {
			printf("fork() was failed\n");
		} else if(childPID > 0){ //parent
			wait(&status);
			total += (data_t)(end - start - overhead);	
		} else if(childPID == 0) { //child
			if(i != 0 && i % 500 == 0) {
				printf(".");
			}

			exit(1);
		}
	}
	
	printf("\n");

	return (total/TASK_CREATION_NUM);
}

