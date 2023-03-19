all: compute node

compute:
	gcc -Wall -Werror -Wextra -o compute manager/*.c -lzmq

node:
	gcc -o worker/worker worker/worker.c -lzmq

run:
	./compute

clean:
	rm worker/worker compute