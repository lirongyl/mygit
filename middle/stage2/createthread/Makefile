target=createthread
objects=createthread.o

$(target):$(objects)
	gcc -o $(target) $(objects) -lpthread
$(objects):
	gcc -c createthread.c -lpthread 
.PHONY:clean
clean:
	-rm -f $(objects) $(target)
