# Makefile
all: zad1 clean

zad1: main1.o zad1.o
	gcc -o zad1 main1.o zad1.o

main1.o: main1.c
	gcc -c main1.c

zad1.o: zad1.c
	gcc -c zad1.c

clean:
	rm -f *.o