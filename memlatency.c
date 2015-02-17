#include "cpu_test.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/stat.h>
#include <math.h>

const int LATENCY_ACCESS_TRIALS = 100000000;
//const int LATENCY_ACCESS_TRIALS = 1000000;
//const int LATENCY_ACCESS_TRIALS = 1000;
size_t INT_SIZE = sizeof(int);
//256B
const size_t array_size0 = 256;
//512B
const size_t array_size1 = 256*2;
//1KB
const size_t array_size2 = 256*4;
//2KB
const size_t array_size3 = 256*8;
//4KB
const size_t array_size4 = 256*16;
//8KB
const size_t array_size5 = 256*32;
//16KB
const size_t array_size6 = 256*64;
//32KB
const size_t array_size7 = 256*128;
//64KB
const size_t array_size8 = 256*256;
//128KB
const size_t array_size9 = 256*512;
//256KB
const size_t array_size10 = 256*1024;
//512KB
const size_t array_size11 = 256*2048;
//1MB
const size_t array_size12 = 256*4096;
//2MB
const size_t array_size13 = 256*8192;
//4MB
const size_t array_size14 = 256*16384;
//8MB
const size_t array_size15 = 256*32768;

data_t memory_latency_helper(data_t, size_t);
void make_cyclic_array(void *, size_t);


data_t memory_latency(data_t ccnt_overhead)
{
	memory_latency_helper(ccnt_overhead, array_size0);
	memory_latency_helper(ccnt_overhead, array_size1);
	memory_latency_helper(ccnt_overhead, array_size2);
	memory_latency_helper(ccnt_overhead, array_size3);
	memory_latency_helper(ccnt_overhead, array_size4);
	memory_latency_helper(ccnt_overhead, array_size5);
	memory_latency_helper(ccnt_overhead, array_size6);
	memory_latency_helper(ccnt_overhead, array_size7);
	memory_latency_helper(ccnt_overhead, array_size8);
	memory_latency_helper(ccnt_overhead, array_size9);
	memory_latency_helper(ccnt_overhead, array_size10);
	memory_latency_helper(ccnt_overhead, array_size11);
	memory_latency_helper(ccnt_overhead, array_size12);
	memory_latency_helper(ccnt_overhead, array_size13);
	memory_latency_helper(ccnt_overhead, array_size14);
	memory_latency_helper(ccnt_overhead, array_size15);
	return 0;
}

data_t memory_latency_helper(data_t ccnt_overhead, size_t size)
{
	unsigned start, end;
	data_t total=0;
	data_t avg;
	printf("Start %u\n", size);
	int * array = (int *) malloc((size_t) size);
	memset(array, 1, size);
	if(array == NULL)
	{
		printf("Malloc error!");
		exit(1);
	}
	make_cyclic_array(array, size);
	int * cur = array;
	for(unsigned int i=0; i<LATENCY_ACCESS_TRIALS; i++)
	{
		start = ccnt_read();
		cur = (int *) *cur;
		end = ccnt_read();
		total += (data_t) (end-start) - ccnt_overhead;
	}
	avg = total / LATENCY_ACCESS_TRIALS;
	printf("Size: %u\t Average Access Time: %f\n",
			size, avg);
	//printf("Dummy: %d\n", *cur);
	free(array);
	return 0;
}

void make_cyclic_array(void * array, size_t size)
{
	void ** ptrarray =  (void **) array;
	unsigned int arraysize = size / sizeof(void *);
	for (unsigned int i=0; i<arraysize; i++)
	{
		ptrarray[i] = &ptrarray[i];
	}

	srand(0);
	for (unsigned int i=arraysize-1; i>0; i--)
	{
		unsigned int swp = rand() % arraysize;
		void * tmp = ptrarray[i];
		ptrarray[i] = ptrarray[swp];
		ptrarray[swp] = tmp;
	}
}
