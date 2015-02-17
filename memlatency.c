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

//const int LATENCY_ACCESS_TRIALS = 100000000;
const int LATENCY_ACCESS_TRIALS = 1000000;
//const int LATENCY_ACCESS_TRIALS = 1000;
size_t INT_SIZE = sizeof(int);
//256B
const size_t array_size0 = 256;
//512B
const size_t array_size1 = 512;
//1KB
const size_t array_size2 = 1024;
//2KB
const size_t array_size3 = 2048;
//4KB
const size_t array_size4 = 4096;
//8KB
const size_t array_size5 = 8192;
//16KB
const size_t array_size6 = 16384;
//32KB
const size_t array_size7 = 32768;
//64KB
const size_t array_size8 = 65536;
//128KB
const size_t array_size9 = 131072;
//256KB
const size_t array_size10 = 262144;
//512KB
const size_t array_size11 = 524288;
//1MB
const size_t array_size12 = 1048576;
//2MB
const size_t array_size13 = 2097152;
//4MB
const size_t array_size14 = 4194304;
//8MB
const size_t array_size15 = 8388608;

data_t memory_latency_helper(data_t, size_t);


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
	unsigned int stride = 0;
	unsigned int index, dummy;
	data_t total=0;
	data_t avg;
	printf("Start %u\n", size);
	int * array = (int *) malloc((size_t) size);
	if(array == NULL)
	{
		printf("Malloc error!");
		exit(1);
	}
	int * cur = array;
	for(int i=0; i<LATENCY_ACCESS_TRIALS; i++)
	{
		stride = stride + (rand() % size);
		if(stride > size)
		{
			stride = stride % size;
			cur = array + (stride/INT_SIZE);
		}
		start = ccnt_read();
		cur = cur + (stride/INT_SIZE);
		end = ccnt_read();
		total += (data_t) (end-start) - ccnt_overhead;
		//fprintf(stderr, "%u: %5u\n", stride, dummy);
	}
	free(array);
	avg = total / LATENCY_ACCESS_TRIALS;
	printf("Size: %u\t Average Access Time: %f\n",
			size, avg);
	printf("Dummy: %d\n", *cur);
	//return (data_t) dummy;
	return 0;
}
