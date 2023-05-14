CC=g++
CFLAGS=-O -ansi -pedantic -Wall

all: bisection newton

bisection: bisection.cpp

newton: newton.cpp

.cpp:
	$(CC) -o $@ $@.cpp $(CFLAGS)

clean:
	rm bisection newton *~
