CC = gcc
CFLAGS = -g -Wall -D_POSIX_C_SOURCE=200809L -std=c99 -D_POSIX_PTHREAD_SEMANTICS -lpthread

all: hex2dd.out dd2hex.out hostinfo.out echo_client.out echo_server.out

echo: echo_client.out echo_server.out

hex2dd.out: hex2dd.c
	$(CC) -o hex2dd.out hex2dd.c $(CFLAGS)

dd2hex.out: dd2hex.c
	$(CC) -o dd2hex.out dd2hex.c $(CFLAGS)

hostinfo.out: hostinfo.c
	$(CC) -o hostinfo.out hostinfo.c $(CFLAGS)

echo_client.out: echo_client.c csapp.o
	$(CC) -o echo_client.out echo_client.c csapp.o $(CFLAGS)

echo_server.out: echo_server.c csapp.o
	$(CC) -o echo_server.out echo_server.c csapp.o $(CFLAGS)

tiny.out: tiny_server.c csapp.o
	$(CC) -o tiny.out tiny_server.c csapp.o $(CFLAGS)

csapp.o: ../csapp.c ../csapp.h
	$(CC) -c ../csapp.c $(CFLAGS)

clean:
	rm *.out *.o
