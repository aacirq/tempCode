#include <stdio.h>
#include <string.h>

#include "apue.h"

#define BSZ 48

int main() {
  char buf[BSZ];
  FILE *fp;

  printf("initial buffer contents\n");
  memset(buf, 'a', BSZ - 2);
  buf[BSZ - 2] = '\0';
  buf[BSZ - 1] = 'X';
  if ((fp = fmemopen(buf, BSZ, "w+")) == NULL) {
    err_sys("fmemopen error");
  }
  fprintf(fp, "Hello, world");
  printf("before flush: %s\n", buf);
  fflush(fp);
  printf("after flush: %s\n", buf);
  printf("len of string in buf = %ld\n", strlen(buf));

  memset(buf, 'b', BSZ - 2);
  buf[BSZ - 2] = '\0';
  buf[BSZ - 1] = 'X';
  fprintf(fp, "Hello, world");
  fseek(fp, 0, SEEK_SET);
  printf("after fseek: %s\n", buf);
  printf("len of string in buf = %ld\n", strlen(buf));

  memset(buf, 'c', BSZ - 2);
  buf[BSZ - 2] = '\0';
  buf[BSZ - 1] = 'X';
  fprintf(fp, "Hello, world");
  fclose(fp);
  printf("after fclose: %s\n", buf);
  printf("len of string in buf = %ld\n", strlen(buf));

  return 0;
}