CC=g++
CFLAGS=-O2 -ansi -pedantic -Wall -lm -Wno-deprecated-declarations -std=c++20

## for Mac OS X
GLFLAGS = -framework OpenGL -framework GLUT -lobjc

## For Linux (one possibility)
#INCL =
#LDFLAGS = -L/usr/X11R6/lib
#GLFLAGS = -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lm 

## For Linux (another possibility)
#INCL = -I/usr/local/MesaGL/include
#LDFLAGS = -L/usr/local/MesaGL/lib -lpthread
#GLFLAGS = -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lm 

EXE=sandpile sandpile_openGL

all: $(EXE)

sandpile: sandpile.cpp
	$(CC) -o $@ sandpile.cpp $(CFLAGS)

sandpile_openGL: sandpile.cpp
	$(CC) -o $@ sandpile.cpp $(CFLAGS) $(INCL) $(LDFLAGS) -DUSE_OPENGL $(GLFLAGS)

clean:
	rm $(EXE)
