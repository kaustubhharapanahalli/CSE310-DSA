EXEC = PJ3
CC = g++
CFLAGS = -c -Wall

$(EXEC) : clean main.o graph.o minHeap.o
	$(CC) -o $(EXEC) main.o graph.o minHeap.o
	rm -rf main.o
	rm -rf graph.o
	rm -rf minHeap.o

main.o : main.cc graph.cc
	$(CC) $(CFLAGS) main.cc

graph.o : graph.cc 
	$(CC) $(CFLAGS) graph.cc

minHeap.o : minHeap.cc 
	$(CC) $(CFLAGS) minHeap.cc

build: main.o graph.o minHeap.o

clean:
	rm -rf PJ3
