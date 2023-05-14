CC=g++
CFLAGS=-std-c++17 -Wall -pedantic

all: fp-peek fp-err fp-safe

.cpp:
	$(CC) -o $@ $@.cpp $(FLAGS)

fp-peek: fp-peek.cpp bitconvert.h

fp-err: fp-err.cpp bitconvert.h

fp-safe: fp-safe.cpp

clean:
	rm fp-peek fp-err fp-safe *~
