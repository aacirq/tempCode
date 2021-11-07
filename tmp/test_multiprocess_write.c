/**
 * 测试指定O_APPEND时，两个进程同时写入一个文件，是否会相互影响
 */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  int fd = open("ttt.txt", O_RDWR | O_CREAT | O_APPEND, 0775);
  int count;
  if (argc != 2) {
    count = 200;
  } else {
    count = atoi(argv[1]);
    printf("count = %d\n", count);
  }

  if (fork() == 0) {
    // child
    for (int i = 0; i < count; ++i) {
      write(fd, "0000000000000000000\n", 20);
    }
  } else {
    // parent
    for (int i = 0; i < count; ++i) {
      write(fd, "1111111111111111111\n", 20);
    }
  }

  return 0;
}