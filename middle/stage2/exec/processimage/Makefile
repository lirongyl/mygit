target=main
objects=processimage.o

$(target):$(objects)
	gcc -o $(target) $(objects)
$(objects):
	gcc -c processimage.c -Wall
.PHONY:clean
clean:
	-rm -f $(objects) $(target) 
