CC=g++
CFLAGS=-O2 -ansi -pedantic -Wall -std=c++20

EXE=capcount capcount2

all: $(EXE)
	
capcount: capcount.cpp
	$(CC) -o $@ $@.cpp $(CFLAGS)

capcount2: capcount2.cpp rational.hpp
	$(CC) -o $@ $@.cpp $(CFLAGS)

clean:
	rm $(EXE)
