CC=g++
CFLAGS=-O2 -ansi -pedantic -Wall -lm

sumdata: sumdata.o add_methods.o
	$(CC) -o $@ sumdata.o add_methods.o $(CFLAGS)

add_methods.o: add_methods.cpp

.cpp:
	$(CC) -o $@ $@.cpp $(CFLAGS)

.o:
	$(CC) -c $@ $@.cpp $(CFLAGS)

clean:
	rm sumdata *.o
