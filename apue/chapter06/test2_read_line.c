#include "apue.h"

#include <stdio.h>

int main() {
  char buf[4096];

  while (fgets(buf, 4096, stdin) != NULL) {
    if (fputs(buf, stdout) == EOF) {
      err_sys("fputs error");
    }
  }

  if (ferror(stdin)) {
    err_sys("fgets error");
  }

  return 0;
}