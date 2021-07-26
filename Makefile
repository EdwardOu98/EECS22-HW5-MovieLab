# Makefile for hw4, EECS22 Fall 2017 fall 
# Author: Huan Chen
# Modified by: Mihnea Chirila
# Modification: Ali Nickparsa 11/11/2018
# Date:   11/01/2017
CC     = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -Wall -std=c99 -c
LFLAGS = -Wall

OBJS = MovieLab.o FileIO.o MovieIO.o Image.o Movie.o ImageList.o DIPs.o
DEPS = Image.h ImageList.h FileIO.h MovieIO.h DIPs.h Movie.h Constants.h IterativeFilter.h

DESIGN = MovieLab
all: $(DESIGN)
MovieLab: $(OBJS) libFilter.a
	$(CC) $(LFLAGS) $(OBJS) -lm -L. -lFilter -o MovieLab

libFilter.a: DIPs.o IterativeFilter.o
	ar rc libFilter.a DIPs.o IterativeFilter.o
	ranlib libFilter.a

MovieLab.o: MovieLab.c $(DEPS)
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o
FileIO.o: FileIO.c FileIO.h Image.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o
MovieIO.o: MovieIO.c MovieIO.h Movie.h FileIO.h
	$(CC) $(CFLAGS) MovieIO.c -o MovieIO.o
DIPs.o: DIPs.c DIPs.h Image.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o
IterativeFilter.o: IterativeFilter.c IterativeFilter.h Image.h Movie.h
	$(CC) $(CFLAGS) IterativeFilter.c -o IterativeFilter.o
Image.o: Image.c Image.h
	$(CC) $(CFLAGS) Image.c -o Image.o
Movie.o: Movie.c Movie.h Image.h ImageList.h
	$(CC) $(CFLAGS) Movie.c -o Movie.o
ImageList.o: ImageList.c ImageList.h Image.h
	$(CC) $(CFLAGS) ImageList.c -o ImageList.o

clean:
	rm -f *.o *.a *.yuv  $(DESIGN) `find . -name '*.ppm' ! -name 'HSSOE.ppm'`
