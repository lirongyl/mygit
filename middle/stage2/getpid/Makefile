target=getpid
objects=getpid.o

$(target):$(objects)
	gcc -o $(target) $(objects) -Wall
$(objects):
	gcc -c getpid.c -Wall
.PHONY:clean
clean:
	-rm -f $(objects) $(target)
