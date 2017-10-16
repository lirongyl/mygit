target=tsd
objects=tsd.o

$(target):$(objects)
	gcc -o $(target) $(objects) -lpthread
$(objects):
	gcc -c tsd.c -lpthread
.PHONY:clean
clean:
	-rm -f $(objects) $(target)
