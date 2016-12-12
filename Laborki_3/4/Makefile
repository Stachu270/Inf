# Makefile
all: prog clean

prog: main.o newagent.o distance.o north.o south.o east.o west.o
	gcc -o prog main.o newagent.o distance.o north.o south.o east.o west.o

main.o: main.c
	gcc -c main.c

newagent.o: newagent.c
	gcc -c newagent.c

distance.o: distance.c
	gcc -c distance.c

north.o: north.c
	gcc -c north.c

south.o: south.c
	gcc -c south.c

east.o: east.c
	gcc -c east.c

west.o: west.c
	gcc -c west.c	

clean:
	rm -f *.o