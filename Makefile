CC = gcc
CFLAGS = -Wall -Wextra -Werror -o
COMP_OBJS = manager/*.c list/list.c
WORK_OBJS = worker/worker.c map/map.c

all: compute node

compute:
	gcc $(CFLAGS) compute $(COMP_OBJS) -lzmq

node:
	gcc $(CFLAGS) worker/worker $(WORK_OBJS) -lzmq

run:
	./compute

clean:
	rm worker/worker compute

format:
	clang-format -i */*