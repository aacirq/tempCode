#include "../csapp.h"

int main(int argc, char *argv[]) {
  rio_t rio;
  int clientfd;
  char buf[MAXLINE];
  char ret_buf[MAXLINE];

  if (argc != 3) {
    fprintf(stderr, "usage: ./echo_client <host> <port>\n");
    exit(1);
  }

  clientfd = Open_clientfd(argv[1], argv[2]);
  Rio_readinitb(&rio, clientfd);

  while (Fgets(buf, MAXLINE, stdin) != NULL) {
    Rio_writen(clientfd, buf, strlen(buf));
    Rio_readlineb(&rio, ret_buf, MAXLINE);
    Fputs(ret_buf, stdout);
  }

  close(clientfd);

  return 0;
}