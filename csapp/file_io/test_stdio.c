#include <stdio.h>

#define MAXLINE 4096

int main() {
  char buf[MAXLINE];

  size_t n;
  while ((n = fread(buf, 1, MAXLINE, stdin)) != 0) {
    fwrite(buf, 1, n, stdout);
  }
  return 0;
}