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
	time_t start, end;

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
    fgets(buffer,WINDOWSIZE-1,stdin);
	start = time(NULL);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");

    bzero(buffer,WINDOWSIZE);
    n = read(sockfd,buffer,WINDOWSIZE-1);
	end = time(NULL);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
	printf("%ld\n",(long) (end-start));
    close(sockfd);
    return 0.0;
}
