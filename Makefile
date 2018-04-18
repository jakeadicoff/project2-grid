CC = g++
CFLAGS = -std=c++11 -Wall

grid: main.o grid.o
	$(CC) -o $@ main.o grid.o

main.o : main.cpp main.h
	$(CC) -c $(CFLAGS) main.cpp -o $@

grid.o : grid.cpp grid.h
	$(CC) -c $(CFLAGS) grid.cpp -o $@

clean:
	rm *.o
	rm  grid
