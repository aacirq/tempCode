#include "rio.h"

#include <unistd.h>

#define MAXLINE 4096

int main(int argc, char *argv[]) {
  rio_t rio;
  int n;
  char buf[MAXLINE];

  rio_readinitb(&rio, STDIN_FILENO);
  while ((n = rio_readlineb(&rio, buf, MAXLINE)) != 0) {
    rio_writen(STDOUT_FILENO, buf, n);
  }

  return 0;
}