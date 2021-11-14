CC=g++
CFLAGS=--std=c++17 -c -O3
all: cw

cw: main.o funcs.o
	$(CC) funcs.o main.o -o courswork

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

funcs.o: funcs.cpp
	$(CC) $(CFLAGS) funcs.cpp

clean:
	rm -rf *.o courswork