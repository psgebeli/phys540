CC=g++ -O2 -std=c++17 -Wall -Wno-deprecated-declarations
CFLAGS=-O2 -ansi -pedantic -Wall

GLFLAGS=`./glflags.bash`

## for Mac OS X
#GLFLAGS = -framework OpenGL -framework GLUT -lobjc

## For Linux (ugl-1xx series machines)
#INCL =
#LDFLAGS = -L/usr/X11R6/lib
#GLFLAGS = -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lm 

## For Linux (ugl-2xx series machines)
#INCL = -I/usr/local/MesaGL/include
#LDFLAGS = -L/usr/local/MesaGL/lib -lpthread
#GLFLAGS = -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lm 

EXE=cannon cannon.o cannon_openGL.o

cannon: cannon.o cannon_openGL.o
	$(CC) -o $@ cannon.o cannon_openGL.o $(LDFLAGS) $(GLFLAGS)

cannon.o: cannon.cpp
	$(CC) -c cannon.cpp $(CFLAGS)

cannon_openGL.o: cannon_openGL.cpp cannon.h
	$(CC) -c cannon_openGL.cpp $(CFLAGS)

clean:
	rm $(EXE) *.o
