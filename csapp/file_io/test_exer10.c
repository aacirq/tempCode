#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "rio.h"
#define MAXLINE 4096

int main(int argc, char *argv[]) {
  rio_t rio;
  int n;
  char buf[MAXLINE];
  int fd;

  if (argc > 2) {
    fprintf(stderr, "%s\n", "usage: a.out OR a.out <infile>");
    exit(1);
  }

  if (argc == 2) {
    if ((fd = open(argv[1], O_RDONLY, 0)) < 0) {
      fprintf(stderr, "error: %s\n", strerror(errno));
      exit(1);
    }
    dup2(fd, STDIN_FILENO);
  }

  rio_readinitb(&rio, STDIN_FILENO);
  while ((n = rio_readlineb(&rio, buf, MAXLINE)) != 0) {
    rio_writen(STDOUT_FILENO, buf, n);
  }

  return 0;
}