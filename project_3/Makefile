EXEC = PJ2
CC = g++
CFLAGS = -c -Wall

$(EXEC) : clean main.o heap.o util.o
	$(CC) -o $(EXEC) main.o heap.o util.o
	rm -rf main.o
	rm -rf heap.o
	rm -rf util.o

main.o : main.cpp heap.cpp util.cpp 
	$(CC) $(CFLAGS) main.cpp

heap.o : heap.cpp
	$(CC) $(CFLAGS) heap.cpp

util.o : util.cpp
	$(CC) $(CFLAGS) util.cpp

build: main.o util.o heap.o

clean:
	rm -rf PJ2
