
.PHONY: all clean

all: a.out

a.out: main.o add.o sub.o mul.o apc.o div.o
	gcc main.o add.o sub.o mul.o apc.o div.o -o a.out

main.o: main.c apc.h
	gcc -c main.c -o main.o

add.o: add.c apc.h
	gcc -c add.c -o add.o

sub.o: sub.c apc.h
	gcc -c sub.c -o sub.o

mul.o: mul.c apc.h
	gcc -c mul.c -o mul.o

apc.o: apc.c apc.h
	gcc -c apc.c -o apc.o

div.o: div.c apc.h
	gcc -c div.c -o div.o

clean:
	rm -f *.o a.out 
