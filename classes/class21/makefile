CC=g++
CFLAGS=-O2 -ansi -pedantic -Wall -std=c++17

RS=rustc

dice: dice.cpp
	$(CC) -o $@ $@.cpp $(CFLAGS)

logistic: logistic.rs
	$(RS) $@.rs

clean:
	rm dice logistic

