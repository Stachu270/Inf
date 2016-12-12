# Makefile
all: zad2 clean

zad2: main2.o zad2.o
	gcc -o zad2 main2.o zad2.o

main2.o: main2.c
	gcc -c main2.c

zad2.o: zad2.c
	gcc -c zad2.c

clean:
	rm -f *.o