CFLAGS=-Wall -g

all: ex1 ex3 #builds all with just command make

clean:
	rm -f ex1 ex2

.PHONY: all clean
