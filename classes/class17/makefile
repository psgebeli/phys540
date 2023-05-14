CC=g++
CFLAGS=-O2 -ansi -pedantic -Wall -std=c++17

RS=rustc
RSFLAGS=-O

EXE=integrate rng pi pi-mp

all: $(EXE)
	
integrate: integrate.cpp 
	$(CC) -o $@ $@.cpp $(CFLAGS)
	
rng: rng.rs
	$(RS) -o $@ $@.rs $(RSFLAGS)

pi: pi.rs
	$(RS) -o $@ $@.rs $(RSFLAGS)

pi-mp: pi-mp.rs
	$(RS) -o $@ $@.rs $(RSFLAGS)

clean:
	rm $(EXE)
