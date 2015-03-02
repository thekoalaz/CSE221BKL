#include "net_test.h"

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

void peakbandwidth_server()
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[WINDOWSIZE];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	   error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = SOCKETNO;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
			sizeof(serv_addr)) < 0) 
			error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	for(int i=0; i<SEND_COUNT * TRIAL_COUNT; i++)
	{
		if(i%SEND_COUNT == 0)
		{
			printf("======================================================================\n");
			printf("Probably in trial %d\n", (int) (i / TRIAL_COUNT + 1));
			printf("Starting server.\n");
			newsockfd = accept(sockfd, 
					  (struct sockaddr *) &cli_addr, 
					  &clilen);
			if (newsockfd < 0) 
				error("ERROR on accept");
		}
		bzero(buffer,WINDOWSIZE);
		n = read(newsockfd,buffer,255);
		if (n < 0) error("ERROR reading from socket");
		n = write(newsockfd,"I got your message",18);
		if (n < 0) error("ERROR writing to socket");
		printf("Message received.\n");
	}
	close(newsockfd);
	close(sockfd);
	return; 
}

int main(int argc, char *argv[])
{
	peakbandwidth_server();
	return 0;
}

