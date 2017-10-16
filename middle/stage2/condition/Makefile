target=condition 
objects=condition.o

$(target):$(objects)
	gcc -o $(target) $(objects) -lpthread
$(objects):
	gcc -c condition.c -lpthread
.PHONY:clean
clean:
	-rm -f $(objects) $(target)
