
all:ctrlpocess monitor

ctrlpocess:ctrlpocess.o
	gcc -o ctrlpocess ctrlpocess.o -Wall
ctrlpocess.o:
	gcc -c ctrlpocess.c -Wall

monitor:monitor.o
	gcc -o monitor monitor.o -Wall
monitor.o:
	gcc -c monitor.c -Wall

.PHONY:clean
clean:
	-rm -f monitor monitor.o ctrlpocess ctrlpocess.o

