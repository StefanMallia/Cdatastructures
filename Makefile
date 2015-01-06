CC = gcc
CFLAGS = -Wall -g
DEPS = LINKEDLIST.h RINGBUFFER.h
OBJ = Client.c LINKEDLIST.c RINGBUFFER.c

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

Client: $(OBJ)
	gcc $(CFLAGS) -o $@ $^
