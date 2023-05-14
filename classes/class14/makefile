CC=g++
CFLAGS=-O -ansi -pedantic -Wall -std=c++17

matrices: matrices.cpp

linalg: linalg.cpp matrix.hpp matrix-upper-tri.hpp

.cpp:
	$(CC) -o $@ $@.cpp $(CFLAGS)

clean:
	rm matrices linalg *~
