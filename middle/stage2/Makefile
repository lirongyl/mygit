target=program
objects=program.o

$(target):$(objects)
	gcc -o $(target) $(objects) -Wall
$(objects):
	gcc -c program.c -Wall
.PHONY:clean
clean:
	-rm -f $(objects) $(target)
