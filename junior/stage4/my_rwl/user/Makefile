my_rwl: my_rwl.o
	gcc -o my_rwl my_rwl.o -Wall
my_rwl.o:types.h stat.h
	gcc -c ../source/my_rwl.c -Wall
.PHONY:clean
clean:
	-rm -f my_rwl my_rwl.o example_63.c
.PHONY:run
run:
	./my_rwl
