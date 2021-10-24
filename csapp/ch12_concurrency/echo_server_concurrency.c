#include "../csapp.h"

void echo(int fd);
void *thread(void *vargs);

int main(int argc, char **argv) {
  int listenfd;
  socklen_t addrlen;
  int *connfdp;
  struct sockaddr_storage addr;
  char host[MAXLINE];
  char port[MAXLINE];
  pthread_t tid;

  if (argc != 2) {
    fprintf(stderr, "usage: ./echo_server <port>\n");
    exit(1);
  }

  listenfd = Open_listenfd(argv[1]);

  while (1) {
    addrlen = sizeof(struct sockaddr_storage);
    connfdp = malloc(sizeof(int));
    if ((*connfdp = accept(listenfd, (struct sockaddr *)&addr, &addrlen)) == -1) {
      fprintf(stderr, "error: accept %s\n", strerror(errno));
      exit(1);
    }
    getnameinfo((struct sockaddr *)(&addr), addrlen, host, MAXLINE, port, MAXLINE, 0);
    fprintf(stdout, "Get connection from <%s, %s>\n", host, port);

    pthread_create(&tid, NULL, thread, (void *)connfdp);
  }
  return 0;
}

void *thread(void *vargs) {
  int connfd = *(int *)vargs;
  pthread_detach(pthread_self());
  free((int *)vargs);
  echo(connfd);
  close(connfd);
  return NULL;
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