CC=gcc
FLAGS=-O2 -Iinclude -Llib -arch i386

all:
	$(CC) $(FLAGS) -lbass -o bin/nyancat src/nyancat.c
	cp ./lib/libbass.dylib ./bin
	cp ./lib/libbass.so ./bin
	cp ./nyancat.ogg ./bin
