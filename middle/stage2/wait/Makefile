target=wait
objects=wait.o

$(target):$(objects)
	gcc -o $(target) $(objects) -Wall
$(objects):
	gcc -c wait.c -Wall
.PHONY:clean
clean:
	-rm -f $(objects) $(target)
