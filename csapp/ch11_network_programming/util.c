#include "util.h"

#include <errno.h>
#include <memory.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int open_clientfd(char *hostname, char *port) {
  struct addrinfo *listp;
  struct addrinfo *p;
  struct addrinfo hints;
  int clientfd;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;
  if (getaddrinfo(hostname, port, &hints, &listp) != 0) {
    fprintf(stderr, "error: getaddrinfo %s\n", strerror(errno));
    exit(1);
  }

  for (p = listp; p != NULL; p = p->ai_next) {
    if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) ==
        -1) {
      continue;
    }

    if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1) {
      break;
    }

    close(clientfd);
  }

  freeaddrinfo(listp);

  if (p == NULL) {
    return -1;
  } else {
    return clientfd;
  }
}

int open_listenfd(char *port) {
  struct addrinfo *listp;
  struct addrinfo *p;
  struct addrinfo hints;
  int listenfd;
  int optval = 1;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG | AI_NUMERICSERV;
  if (getaddrinfo(NULL, port, &hints, &listp) != 0) {
    fprintf(stderr, "error: getaddrinfo %s\n", strerror(errno));
    exit(1);
  }

  for (p = listp; p != NULL; p = p->ai_next) {
    if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) ==
        -1) {
      continue;
    }

    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval,
               sizeof(int));

    if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) {
      break;
    }

    close(listenfd);
  }

  freeaddrinfo(listp);
  if (p == NULL) {
    return -1;
  }

  if (listen(listenfd, 1024) == -1) {
    close(listenfd);
    return -1;
  }
  return listenfd;
}