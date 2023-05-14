CC=g++
EXE=triples triplespg selection moments
CFLAGS=-O2 -ansi -pedantic -Wall -lm

all: $(EXE)

triples: triples.cpp

triplespg: triplespg.cpp

selection: selection.cpp

moments: moments.cpp

.cpp:
	$(CC) -o $@ $@.cpp $(CFLAGS)

.PHONY: clean

clean:
	rm $(EXE)
