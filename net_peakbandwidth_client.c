#include "net_test.h"
#include <netdb.h>

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

data_t peakbandwidth_client(data_t ccnt_overhead)
{
	int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
	data_t start, end;
	float total = 0.0;
	float avg = 0.0;
	float stddev = 0.0;
	float max = 0.0; 
    float min = 10000000.0;

    char buffer[WINDOWSIZE];
    portno = SOCKETNO;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
       error("ERROR opening socket");
    server = gethostbyname(SERVER_IP);
    if (server == NULL) {
       fprintf(stderr,"ERROR, no such host\n");
       exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
       error("ERROR connecting");
    //printf("Please enter the message: ");
    bzero(buffer,WINDOWSIZE);
    //fgets(buffer,WINDOWSIZE-1,stdin);
	printf("%ld\n", (long) time(NULL));
	srand((long) time(NULL));
	for (int i=0; i<WINDOWSIZE-1; i++)
	{
		buffer[i] = (char) rand() + 1;
	}

	for(int i=0; i<SEND_COUNT; i++)
	{
		start = ccnt_read();
		n = write(sockfd,buffer,strlen(buffer));
		if (n < 0) 
			error("ERROR writing to socket");

		n = read(sockfd,buffer,WINDOWSIZE-1);
		end = ccnt_read();
		if (n < 0) 
			error("ERROR reading from socket");
		printf("Message returned\n");

		float latency = (end-start) - ccnt_overhead ;
		printf("%f\n", latency);
		float prev_avg = avg;
		unsigned int k = i + 1;
		total += latency;
		avg += (latency - avg) / k;
		stddev += ((float) (k-1))/k * (latency - prev_avg) * (latency - prev_avg);
		if(latency > max) { max = latency; }
		if(latency < min) { min = latency; }
	}
	stddev = sqrt(stddev);
	printf("Total: %f\t Average Send Time: %f\t Max: %f\t Min: %f\t Std. Dev: %f\n",
			total, avg, max, min, stddev);
    close(sockfd);
    return total;
}

data_t peakbandwidth(data_t ccnt_overhead)
{
	float avg = 0.0;
	float stddev = 0.0;
	float max = 0.0; 
    float min = 1000000000.0;

	for(int i=0; i<TRIAL_COUNT; i++)
	{
		sleep(3);

		float latency = peakbandwidth_client(ccnt_overhead);
		float prev_avg = avg;
		unsigned int k = i + 1;
		avg += (latency - avg) / k;
		stddev += ((float) (k-1))/k * (latency - prev_avg) * (latency - prev_avg);
		if(latency > max) { max = latency; }
		if(latency < min) { min = latency; }
	}

	stddev = sqrt(stddev);
	printf("Average Send Time: %f\t Max: %f\t Min: %f\t Std. Dev: %f\n",
			avg, max, min, stddev);

	return avg;
}

