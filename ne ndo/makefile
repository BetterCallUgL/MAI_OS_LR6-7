CC = gcc
CFLAGS = -lzmq

all: server client

server:
	gcc -Wall -g client.c -lzmq -o server

client:
	gcc -Wall -g node.c -lzmq -o client

clean:
	rm server client

