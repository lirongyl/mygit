target = main
objects = main.o

$(target):$(objects)
	gcc -o $(target) $(objects) -Wall
$(objects):
	gcc -c $(target).c -Wall

.PHONY:clean
clean:
	-rm -f $(objects) $(target)

