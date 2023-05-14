CC=clang++
CFLAGS=-O

all: pascal smooth

pascal: pascal.cpp
	$(CC) -o $@ $@.cpp $(CFLAGS)

smooth: smooth.cpp
	$(CC) -o $@ $@.cpp $(CFLAGS)

clean:
	rm pascal smooth *~
