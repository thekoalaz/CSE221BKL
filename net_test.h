#ifndef NET_TEST_H_
#define NET_TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
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
#define SOCKETNO 2222
#define WINDOWSIZE 163840
#define TRIAL_COUNT 10

static const int SEND_COUNT = (int) (10 * 1024 * 1024) / WINDOWSIZE + 1;

//pmu functions
data_t get_overhead();
void pmcr_init();

//measurement functions
data_t peakbandwidth(data_t);

#endif

