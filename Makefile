CC=g++
CFLAGS=-c -Wall -std=c++0x -g -O0
LDFLAGS=#-lstdc++
SOURCES=rpi_pmu.c cpu_process_creation.c cpu_thread_creation.c main.c proccall_test.c syscall_test.c pagefault_test.c memlatency.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=memtest

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ 
#	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE) 
	
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clear: 
	$(RM) $(EXECUTABLE) $(OBJECTS)

test:
	$(CC) test.cpp

