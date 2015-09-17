

all:program

program: Client.o
	gcc Client.c -o Client -L. -lLINKEDLIST -L. -lRINGBUFFER && rm Client.o libLINKEDLIST.a libRINGBUFFER.a

Client.o: Client.c libLINKEDLIST.a libRINGBUFFER.a
	gcc -c Client.c

libLINKEDLIST.a: LINKEDLIST.c
	gcc -c LINKEDLIST.c -o LINKEDLIST.o && ar rcs libLINKEDLIST.a -o LINKEDLIST.o  && rm LINKEDLIST.o

libRINGBUFFER.a: RINGBUFFER.c
	gcc -c RINGBUFFER.c -o RINGBUFFER.o && ar rcs libRINGBUFFER.a -o RINGBUFFER.o  && rm RINGBUFFER.o


clean:
	rm Client
