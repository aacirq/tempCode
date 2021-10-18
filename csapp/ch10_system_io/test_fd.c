#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  int fd1, fd2;
  fd1 = open("rio.c", O_RDONLY, 0);
  fd2 = open("rio.h", O_RDONLY, 0);
  close(fd2);
  fd2 = open("rio.o", O_RDONLY, 0);
  printf("fd2 = %d\n", fd2);

  return 0;
}