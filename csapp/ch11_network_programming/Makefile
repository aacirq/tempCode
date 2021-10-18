CC = gcc
CFLAGS = -Wall

all: hex2dd.out dd2hex.out

hex2dd.out: hex2dd.c
	$(CC) -o hex2dd.out hex2dd.c $(CFLAGS)

dd2hex.out: dd2hex.c
	$(CC) -o dd2hex.out dd2hex.c $(CFLAGS)

clean:
	rm *.out
