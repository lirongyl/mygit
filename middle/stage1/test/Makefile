all:test_client test_server

prog1 = test_server
objs1 = test_server.o 
sour1 = test_server.c
prog2 = test_client
objs2 = test_client.o
sour2 = test_client.c

$(prog1):$(objs1)
	gcc -o $(prog1) $(objs1) -Wall
$(objs1):
	gcc -c $(sour1) -Wall

$(prog2):$(objs2)
	gcc -o $(prog2) $(objs2) -Wall
$(objs2):
	gcc -c $(sour2) -Wall


.PHONY:clean
clean:
	-rm -f $(prog1) $(objs1) $(prog2) $(objs2)
