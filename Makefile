CC=g++
CFLAGS=-c -Wall -std=c++0x -g -O0
LDFLAGS=#-lstdc++

CPU_SOURCES=rpi_pmu.c cpu_main.c cpu_process_creation.c cpu_thread_creation.c proccall_test.c syscall_test.c
CPU_OBJECTS=$(CPU_SOURCES:.c=.o)
CPU_EXECUTABLE=cpu_test

MEM_SOURCES=rpi_pmu.c mem_main.c pagefault_test.c mem_latency.c
MEM_OBJECTS=$(MEM_SOURCES:.c=.o)
MEM_EXECUTABLE=mem_test

NET_SOURCES=rpi_pmu.c net_main.c net_peakbandwidth_client.c net_peakbandwidth_server.c
NET_OBJECTS=$(NET_SOURCES:.c=.o)
NET_EXECUTABLE=net_test

all: cpu mem net
cpu: $(CPU_SOURCES) $(CPU_EXECUTABLE)
mem: $(MEM_SOURCES) $(MEM_EXECUTABLE)
net: $(NET_SOURCES) $(NET_EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ 

$(CPU_EXECUTABLE): $(CPU_OBJECTS) 
	$(CC) $(LDFLAGS) $(CPU_OBJECTS) -o $@ 
	
$(MEM_EXECUTABLE): $(MEM_OBJECTS) 
	$(CC) $(LDFLAGS) $(MEM_OBJECTS) -o $@ 

$(NET_EXECUTABLE): $(NET_OBJECTS) 
	$(CC) $(LDFLAGS) $(NET_OBJECTS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clear: 
	$(RM) $(CPU_EXECUTABLE) $(CPU_OBJECTS)
	$(RM) $(MEM_EXECUTABLE) $(MEM_OBJECTS)
	$(RM) $(NET_EXECUTABLE) $(NET_OBJECTS)

test:
	$(CC) test.cpp

