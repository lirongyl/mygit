fcntl_access: fcntl_access.o
	gcc -o fcntl_access fcntl_access.o -Wall
fcntl_access.o:
	gcc -c ../source/fcntl_access.c -Wall
.PHONY:clean
clean:
	-rm -f fcntl_access.o fcntl_access example
.PHONY:run
run:
	./fcntl_access
