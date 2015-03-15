CC=g++
CFLAGS=-c -Wall -std=c++0x -g -O0
LDFLAGS=#-lstdc++

CPU_SOURCES=rpi_pmu.c cpu_main.c cpu_process_creation.c cpu_thread_creation.c proccall_test.c syscall_test.c
CPU_OBJECTS=$(CPU_SOURCES:.c=.o)
CPU_EXECUTABLE=cpu_test

MEM_SOURCES=rpi_pmu.c mem_main.c pagefault_test.c mem_latency.c
MEM_OBJECTS=$(MEM_SOURCES:.c=.o)
MEM_EXECUTABLE=mem_test

NET_PEAKBW_SOURCES=rpi_pmu.c net_peakbw_main.c net_peakbw_client.c
NET_PEAKBW_OBJECTS=$(NET_PEAKBW_SOURCES:.c=.o)
NET_PEAKBW_EXECUTABLE=net_peakbw_test
NET_PEAKBW_SERVER_SOURCES=rpi_pmu.c net_peakbw_server.c
NET_PEAKBW_SERVER_OBJECTS=$(NET_PEAKBW_SERVER_SOURCES:.c=.o)
NET_PEAKBW_SERVER_EXECUTABLE=net_peakbw_server

FS_READTIME_SOURCES=rpi_pmu.c fs_read_time.c
FS_READTIME_EXECUTABLE=fs_read_time
FS_READTIME_OBJECTS=$(FS_READTIME_SOURCES:.c=.o)

all: cpu mem net_peakbw fs_read
cpu: $(CPU_SOURCES) $(CPU_EXECUTABLE)
mem: $(MEM_SOURCES) $(MEM_EXECUTABLE)
peakbw_client: $(NET_PEAKBW_SOURCES) $(NET_PEAKBW_EXECUTABLE)
peakbw_server: $(NET_PEAKBW_SERVER_SOURCES) $(NET_PEAKBW_SERVER_EXECUTABLE)
net_peakbw: peakbw_client peakbw_server
fs_read: $(FS_READTIME_SOURCES) $(FS_READTIME_EXECUTABLE)


$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ 

$(CPU_EXECUTABLE): $(CPU_OBJECTS) 
	$(CC) $(LDFLAGS) $(CPU_OBJECTS) -o $@ 
	
$(MEM_EXECUTABLE): $(MEM_OBJECTS) 
	$(CC) $(LDFLAGS) $(MEM_OBJECTS) -o $@ 

$(NET_PEAKBW_EXECUTABLE): $(NET_PEAKBW_OBJECTS) 
	$(CC) $(LDFLAGS) $(NET_PEAKBW_OBJECTS) -o $@ 
$(NET_PEAKBW_SERVER_EXECUTABLE): $(NET_PEAKBW_SERVER_OBJECTS) 
	$(CC) $(LDFLAGS) $(NET_PEAKBW_SERVER_OBJECTS) -o $@ 

$(FS_READTIME_EXECUTABLE) : $(FS_READTIME_OBJECTS)
	$(CC) $(LDFLAGS) $(FS_READTIME_OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clear: 
	$(RM) $(CPU_EXECUTABLE) $(CPU_OBJECTS)
	$(RM) $(MEM_EXECUTABLE) $(MEM_OBJECTS)
	$(RM) $(NET_PEAKBW_EXECUTABLE) $(NET_PEAKBW_OBJECTS)
	$(RM) $(NET_PEAKBW_SERVER_EXECUTABLE) $(NET_PEAKBW_SERVER_OBJECTS)
	$(RM) $(FS_READTIME_EXECUTABLE) $(FS_READTIME_OBJECTS)

test:
	$(CC) test.cpp

