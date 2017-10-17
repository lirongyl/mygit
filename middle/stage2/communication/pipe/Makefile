all:server client
objs=server client server.o client.o

server:server.o
	gcc -o server server.o
client:client.o
	gcc -o client client.o
server.o:
	gcc -c server.c
client.o:
	gcc -c client.c

.PHONY:clean
clean:
	-rm -f $(objs)

