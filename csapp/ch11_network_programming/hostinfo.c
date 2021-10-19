#include <errno.h>
#include <memory.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

#ifndef MAXLINE
#define MAXLINE 4096
#endif

int main(int argc, char *argv[]) {
  struct addrinfo *p, *listp;
  struct addrinfo hints;
  char buf[MAXLINE];
  int flags;

  if (argc < 2) {
    fprintf(stderr, "usage: ./hostinfo <domain-name>\n");
    exit(1);
  }

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if (getaddrinfo(argv[1], NULL, &hints, &listp) != 0) {
    fprintf(stderr, "error: getaddrinfo %s\n", strerror(errno));
    exit(1);
  }

  flags = NI_NUMERICHOST;
  for (p = listp; p != NULL; p = p->ai_next) {
    if (getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags) != 0) {
      fprintf(stderr, "error: getnameinfo %s\n", strerror(errno));
      exit(1);
    }
    fprintf(stdout, "%s\n", buf);
  }

  freeaddrinfo(listp);

  return 0;
}