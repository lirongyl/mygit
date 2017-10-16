target=main
objects=execve.o

$(target):$(objects)
	gcc -o $(target) $(objects) -Wall
$(objects):
	gcc -c execve.c -Wall
.PHONY:clean
clean:
	-rm -f $(objects) $(target)
