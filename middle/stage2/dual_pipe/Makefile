target=dual_pipe
objects=dual_pipe.o

$(target):$(objects)
	gcc -o $(target) $(objects) -Wall
$(objects):
	gcc -c dual_pipe.c -Wall
.PHONY:clean
clean:
	-rm -f $(objects) $(target)
