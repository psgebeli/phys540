CC=g++
CFLAGS=-O2 -Wall -ansi -pedantic -std=c++20

all: $(patsubst %.cpp,%,$(wildcard slm*.cpp))

.cpp:
	$(CC) -o $@ $@.cpp $(CFLAGS)

clean:
	rm $(patsubst %.cpp,%,$(wildcard slm*.cpp))
