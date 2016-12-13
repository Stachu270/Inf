# Makefile
all: prog clean

prog: main.o nwd.o phi.o
	gcc -o prog main.o nwd.o phi.o

main.o: main.c
	gcc -c main.c

nwd.o: nwd.c
	gcc -c nwd.c

phi.o: phi.c
	gcc -c phi.c

clean:
	rm -f *.o