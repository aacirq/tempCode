CC = gcc
CFLAGS = -Wall -D_POSIX_C_SOURCE=200112L

all: hex2dd.out dd2hex.out

hex2dd.out: hex2dd.c
	$(CC) -o hex2dd.out hex2dd.c $(CFLAGS)

dd2hex.out: dd2hex.c
	$(CC) -o dd2hex.out dd2hex.c $(CFLAGS)

hostinfo.out: hostinfo.c
	$(CC) -o hostinfo.out hostinfo.c $(CFLAGS)

clean:
	rm *.out
