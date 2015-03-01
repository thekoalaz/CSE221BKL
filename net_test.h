#ifndef NET_TEST_H_
#define NET_TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "parameter.h"
#include "rpi_pmu.h"


//debugging variables
#define DEBUG

//constants
#define CLIENT_IP = "132.239.10.230"
#define SERVER_IP = "132.239.10.66"

//network functions


//pmu functions
data_t get_overhead();
void pmcr_init();

//measurement functions
data_t cpu_process_creation(data_t);
data_t cpu_thread_creation(data_t);

data_t* cpu_proccall_overhead(data_t ccnt_overhead);
data_t cpu_syscall_overhead(data_t ccnt_overhead);

#endif

