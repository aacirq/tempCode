CC = gcc
CFLAGS = -g -Wall -D_POSIX_C_SOURCE=200809L -std=c99 -D_POSIX_PTHREAD_SEMANTICS -lpthread

echo_server.out: echo_server_concurrency.c csapp.o
	$(CC) -o echo_server echo_server_concurrency.c csapp.o $(CFLAGS)

pthread_hello.out: pthread_hello.c csapp.o
	$(CC) -o pthread_hello.out pthread_hello.c csapp.o $(CFLAGS)

csapp.o: ../csapp.h ../csapp.c
	$(CC) -c ../csapp.c $(CFLAGS)

clean:
	rm *.out *.o echo_server pthread_hello
