#ifndef NET_TEST_H_
#define NET_TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "parameter.h"
#include "rpi_pmu.h"

//debugging variables
#define DEBUG

//constants
#define CLIENT_IP "132.239.10.230"
#define SERVER_IP "132.239.10.66"
#define SOCKETNO 2222;

//pmu functions
data_t get_overhead();
void pmcr_init();

//measurement functions
data_t peakbandwidth_client(data_t);

#endif

