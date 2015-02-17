#include "cpu_test.h"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"

#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/stat.h>


const int PAGE_SIZE = 4096;

//const int MAX_MEM_SIZE = 512*1024*1024; //(Bytes)
const int MAX_MEM_SIZE = 512*1024*400;
const int ITER_SIZE = 120583;
const int MAX_ARRAY_SIZE = 512*1024*1024/4/4;

typedef struct LList_{
	struct LList_ *next;
	//int data[PAGE_SIZE/sizeof(int)-1];
	int *data;
} LList;

/*
data_t  pagefault_test3(data_t ccnt_overhead)
{
	int i,j;
	data_t total_fault = 0;
	data_t total_notfault = 0;

	LList *head;
	LList *temp;
	LList *temp_next;
	head = (LList*)malloc(sizeof(LList));
	temp= (LList*)malloc(sizeof(LList));

	head->next = temp;

	for(i=0;i<=ITER_SIZE;i++){
		temp_next = (LList*)malloc(sizeof(LList));
		temp_next->data = (int*) malloc(sizeof(int)*1024);
		for(j=0;j<1024;j++){
			temp_next->data[i] = 123;
		}
		temp->next = temp_next;
		temp = temp_next;
#ifdef DEBUG
		printf("%dth ptr allocated\n", i);
#endif
	}
}
*/

data_t pagefault_test(data_t ccnt_overhead)
{
	unsigned start, end;
	data_t total_fault = 0;
	data_t total_notfault = 0;
	int fd;
	int i, j, temp;
	char *file = NULL;
	int flag = PROT_WRITE | PROT_READ ;
	ssize_t s;

	if(fd = open("pgfault_test.txt", O_RDWR|O_CREAT)<0){
		printf("File open error\n");
	}

	//file = (char *)malloc(MAX_MEM_SIZE * 2);

	if((file=(char*)mmap(NULL,MAX_MEM_SIZE * 2,flag,MAP_SHARED|MAP_ANONYMOUS,fd,0))==NULL){
		printf("mmap error\n");
	}

//	s = write(STDOUT_FILENO, file + 0, sizeof(int)*4);

	for(i=0;i<MAX_MEM_SIZE;i++){
		memset(file + i,'a',1);
	}

	for(i=0;i<MAX_MEM_SIZE;i = i + 1024){
		start = ccnt_read();
		temp = file[i];
		end = ccnt_read();
		total_notfault += (data_t)(end-start)-ccnt_overhead;
#ifdef DEBUG
//		printf("No pgfault: %d\t\t%f\n", i, (float)(end-start));
#endif
	}
	printf("memread speed without page fault: %f\n", (float)total_notfault*1024/MAX_MEM_SIZE);

	for(i=MAX_MEM_SIZE;i<MAX_MEM_SIZE*2;i++){
		memset(file + i,'a',1);
	}

	for(i=0;i<MAX_MEM_SIZE;i = i + 1024){
		start = ccnt_read();
		temp = file[i];
		end = ccnt_read();
		total_fault += (data_t)(end-start)-ccnt_overhead;
#ifdef DEBUG
//		printf("Pgfault: %d\t\t%f\n", i, (float)(end-start));
#endif
	}
	printf("memread speed with page fault: %f\n", (float)total_fault*1024/MAX_MEM_SIZE);



	return total_fault;
}


/*
data_t pagefault_test1(data_t ccnt_overhead)
{
	unsigned start, end;
	data_t total_notfault = 0;
	data_t total_fault = 0;
	data_t total_temp = 0;
	int i,j;
	int arr1[MAX_ARRAY_SIZE];
	int arr2[MAX_ARRAY_SIZE];
	int temp;

	for(i=0;i<MAX_ARRAY_SIZE;i++){
		arr1[i] = 123;
	}
	
	for(i=0;i<MAX_ARRAY_SIZE;i++){
		arr2[i] = 123;
	}


	for(i=0;i<PAGEFAULT_TEST_NUM;i++){
		total_temp = 0;
		for(j=0; j<MAX_ARRAY_SIZE; j++){
			start = ccnt_read();
			temp = arr2[i];
			end = ccnt_read();
			total_temp = (data_t)(end - start - ccnt_overhead);
		}
		total_notfault += total_temp/MAX_ARRAY_SIZE;
	}
	total_notfault /= PAGEFAULT_TEST_NUM;
	

	for(i=0;i<PAGEFAULT_TEST_NUM;i++){
		total_temp = 0;
		for(j=0; j<MAX_ARRAY_SIZE; j++){
			start = ccnt_read();
			temp = arr1[i];
			end = ccnt_read();
			total_temp = (data_t)(end - start - ccnt_overhead);
		}
		total_fault += total_temp/MAX_ARRAY_SIZE;
	}
	total_fault /= PAGEFAULT_TEST_NUM;

#ifdef DEBUG
	printf("array read without page fault: %f\n", (float)total_notfault);
	printf("array read with page fault: %f\n", (float)total_fault);
#endif

	return total_fault;
}
*/
