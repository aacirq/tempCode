#include "../csapp.h"

void echo(int fd);

int main(int argc, char **argv) {
  int listenfd, connfd;
  struct sockaddr_storage addr;
  socklen_t addrlen;
  char host[MAXLINE];
  char port[MAXLINE];

  if (argc != 2) {
    fprintf(stderr, "usage: ./echo_server <port>\n");
    exit(1);
  }

  listenfd = Open_listenfd(argv[1]);

  while (1) {
    addrlen = sizeof(struct sockaddr_storage);
    if ((connfd = accept(listenfd, (struct sockaddr *)&addr, &addrlen)) == -1) {
      fprintf(stderr, "error: accept %s\n", strerror(errno));
      exit(1);
    }
    getnameinfo((struct sockaddr *)(&addr), addrlen, host, MAXLINE, port, MAXLINE, 0);
    fprintf(stdout, "Get connection from <%s, %s>\n", host, port);

    echo(connfd);

    fprintf(stdout, "close connection\n");
    close(connfd);
  }

  return 0;
}

void echo(int fd) {
  rio_t rio;
  int n;
  char buf[MAXLINE];

  Rio_readinitb(&rio, fd);
  while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
    fprintf(stdout, "server recieved %ld bytes\n", strlen(buf));
    Rio_writen(fd, buf, n);
  }
}