EXEC = PJ1
CC = g++
CFLAGS = -c -Wall

$(EXEC) : clean main.o insertion_sort.o merge_sort.o quick_sort.o
	$(CC) -o $(EXEC) main.o insertion_sort.o merge_sort.o quick_sort.o

main.o : main.cpp insertion_sort.cpp merge_sort.cpp quick_sort.cpp
	$(CC) $(CFLAGS) main.cpp

insertion_sort.o : insertion_sort.cpp
	$(CC) $(CFLAGS) insertion_sort.cpp

merge_sort.o : merge_sort.cpp
	$(CC) $(CFLAGS) merge_sort.cpp

quick_sort.o : quick_sort.cpp
	$(CC) $(CFLAGS) quick_sort.cpp

build: main.o merge_sort.o insertion_sort.o quick_sort.o

clean:
	rm -rf PJ1
	rm -rf main.o
	rm -rf insertion_sort.o
	rm -rf merge_sort.o
	rm -rf quick_sort.o