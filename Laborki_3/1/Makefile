# Makefile
all: prog clean

prog: main.o fun1.o
	gcc -o prog main.o fun1.o

main.o: main.c
	gcc -c main.c

fun1.o: fun1.c
	gcc -c fun1.c

clean:
	rm -f *.o