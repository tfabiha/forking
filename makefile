all: main.o
	gcc main.o

main.o:
	gcc -c main.c

run:
	./a.out
