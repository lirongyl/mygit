main: main.o
	gcc -o main main.o -Wall
my_rwl.o:
	gcc -c main.c -Wall
.PHONY:clean
clean:
	-rm -f main main.o 
.PHONY:run
run:
	./main

