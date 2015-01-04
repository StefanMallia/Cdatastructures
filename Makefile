CFLAGS=-Wall -g

all: Tester #builds all with just command make

Tester: LINKEDLIST

clean:
	rm -f ex1 ex2

.PHONY: all clean
