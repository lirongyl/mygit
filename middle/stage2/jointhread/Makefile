target=jointhread
objects=jointhread.o

$(target):$(objects)
	gcc -o $(target) $(objects) -lpthread
$(objects):
	gcc -c jointhread.c -lpthread
.PHONY:clean
clean:
	-rm -f $(objects) $(target)
