CC = gcc
CFLAGS = -Wall -Werror -Wextra -o
OBJS = manager/*.c list/list.c

all: compute node

compute:
	gcc $(CFLAGS) compute $(OBJS) -lzmq

node:
	gcc $(CFLAGS) worker/worker worker/worker.c -lzmq

run:
	./compute

clean:
	rm worker/worker compute