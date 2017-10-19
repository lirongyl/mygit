target = main
objects = main.o

main:main.o
	gcc -o $(target) $(objects) -Wall
main.o:
	gcc -c main.c -Wall

.PHONY:clean
clean:
	-rm -f $(objects) $(target)

