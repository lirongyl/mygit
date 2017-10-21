target=dup
objects=dup.o

$(target): $(objects)
	gcc -o $(target) $(objects) -Wall
$(objects):
	gcc -c ../source/$(target).c -Wall

.PHONY:clean
clean:
	-rm -f $(target) $(objects) example

.PHONY:run
run:
	./$(target)
