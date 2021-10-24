#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void try_open(const char *fname) {
  int fd = open(fname, O_RDWR);
  printf("open(\"%s\") returns %d\n", fname, fd);
  if (fd < 0) {
    perror("  cause");
  } else {
    close(fd);
  }
}

int main() {
  try_open("/something/not/exist");
  try_open("/dev/sda");
  return 0;
}