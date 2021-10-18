#include <stdio.h>

#include "apue.h"

static void pr_stdio(const char *, FILE *);

int main() {
  fputs("enter any character\n", stdout);
  if (getchar() == EOF) {
    err_sys("getchar error");
  }
  fputs("one line to standard error\n", stderr);

  pr_stdio("stdin", stdin);
  pr_stdio("stdout", stdout);
  pr_stdio("stderr", stderr);

  FILE *fp;
  if ((fp = fopen("/etc/passwd", "r")) == NULL) {
    err_sys("fopen error");
  }
  if (getc(fp) == EOF) {
    err_sys("getc error");
  }
  pr_stdio("/etc/passwd", fp);

  return 0;
}

static int is_unbuffered(FILE *fp) {
  return fp->_flags & _IONBF;
}

static int is_linebuffered(FILE *fp) {
  return fp->_flags & _IOLBF;
}

static int buffer_size(FILE *fp) {
  return fp->_IO_buf_end - fp->_IO_buf_base;
}

static void pr_stdio(const char *name, FILE *fp) {
  printf("stream = %s, ", name);
  if (is_unbuffered(fp))
    printf("unbuffered");
  else if (is_linebuffered(fp))
    printf("line buffered");
  else
    printf("fully buffered");
  printf(", buffer size = %d\n", buffer_size(fp));
}
