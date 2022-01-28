/**
 * 测试当两个fd执行同一个文件时，计算两个fd在不同的进程中，也会相互影响
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAXLINE 4096

int main() {
  int fd;
  char buf[MAXLINE];

  fd = open("tmp.txt", O_RDONLY);

  if (fork() == 0) {
    // child process
    read(fd, buf, 2);
    printf("chile process: %s\n", buf);
    exit(0);
  }

  wait(NULL);  // 等待子进程执行结束再继续执行
  // parent process
  read(fd, buf, 2);
  printf("parent process: %s\n", buf);

  return 0;
}
