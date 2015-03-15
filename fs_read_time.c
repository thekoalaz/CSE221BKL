#include "fs_test.h"
#include <float.h>

static const unsigned int FS_READ_TRIALS = 10;
// 4KB = Block size
static const unsigned int BLOCK_SIZE = 4;
static const unsigned int START_SIZE = BLOCK_SIZE;
// 512MB
static const unsigned int END_SIZE = 512 * 1024;
static const unsigned int STRIDE = 2;

int main()
{
	data_t fs_read_time_result;

	pmcr_init();

	//Measurement overhead
	data_t ccnt_overhead;
	ccnt_overhead = get_overhead();
	printf("Reading overhead time is : %f\n", ccnt_overhead);
	
	for(unsigned int size=START_SIZE; size < END_SIZE+1; size *=STRIDE)
	{
		fs_read_time_result = readtime(ccnt_overhead, size, false);
	}
	printf("%f\n", fs_read_time_result);
	for(unsigned int size=START_SIZE; size < END_SIZE+1; size *=STRIDE)
	{
		fs_read_time_result = readtime(ccnt_overhead, size, true);
	}
	printf("%f\n", fs_read_time_result);

	return 0;
}

data_t readtime(data_t ccnt_overhead, unsigned int size, bool random_read)
{
	int fd;
	data_t start, end;
	float total = 0.0;
	float avg = 0.0;
	float stddev = 0.0;
	float max = 0.0; 
	float min = 1000000000000.0;

	char filename[32]; 
	char buf[BLOCK_SIZE * 1024];
	sprintf(filename, FILENAME, size);
	printf("%uKB: \t\t", size);

	for(unsigned int i=0; i<FS_READ_TRIALS; i++)
	{
		if((fd = open(filename, O_SYNC)) == -1 ) 
		{
			printf("Open error\n");
			exit(1);
		}

		float accum = 0.0;
		ssize_t s = 0;
		int count = 0;
		srandom(time(NULL));
		do
		{
			if(random_read)
			{
				unsigned int offset = random() % (size / BLOCK_SIZE);
				if(lseek(fd, offset * BLOCK_SIZE * 1024, SEEK_SET) == -1)
				{
					printf("Seek error\n");
					exit(1);
				}
			}
			start = ccnt_read();
			s += read(fd, buf, BLOCK_SIZE * 1024);
			if(s == -1)
			{
				printf("Read error\n");
				exit(1);
			}
			end = ccnt_read();

			accum += (end-start) - ccnt_overhead;
			count++;
		} while((unsigned int) s < size * 1024);

		//Redo if we encountered bug with ccnt_read.
		if(accum < 0)
		{
			i -=1;
			continue;
		}
		float prev_avg = avg;
		unsigned int k = i + 1;
		total += accum;
		avg += (accum - avg) / k;
		stddev += ((float) (k-1))/k * (accum - prev_avg) * (accum - prev_avg);
		if(accum > max) { max = accum; }
		if(accum < min) { min = accum; }
	}

	stddev = sqrt(stddev/FS_READ_TRIALS);
	printf("Average: %f\t Max: %f\t Min: %f\t Std. Dev: %f\n",
			avg, max, min, stddev);

	close(fd);

	return avg;
}

