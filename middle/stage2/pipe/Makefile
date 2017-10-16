target=pipe
objects=pipe.o

$(target):$(objects)
	gcc -o $(target) $(objects) -Wall
$(objects):
	gcc -c pipe.c -Wall
.PHONY:clean
clean:
	-rm -f $(objects) $(target)
