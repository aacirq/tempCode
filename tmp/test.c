/**
 * 测试同时读写同一个文件会相互影响
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int fd1, fd2;
  char buf[4096];
  ssize_t n1, n2;

  // Prepare test file
  int fd = open("tmp.txt", O_WRONLY|O_CREAT|O_TRUNC);
  if (write(fd, "123456789123456789", 18) != 18) {
    printf("write error\n");
    exit(1);
  }
  // 此时tmp.txt中的内容是123456789123456789

  // Start test
  fd1 = open("tmp.txt", O_RDWR);
  if ((n1 = read(fd1, buf, 5)) < 0) {
    printf("read error\n");
    exit(1);
  }
  printf("read %ld bytes\n", n1);
  printf("%s\n", buf);

  fd2 = open("tmp.txt", O_RDWR);
  lseek(fd2, 10, SEEK_SET);

  char new_val[] = "00000";
  if ((n2 = write(fd2, new_val, 5)) != 5) {
    printf("write error %ld\n", n2);
    exit(1);
  }
  printf("write %ld bytes\n", n2);

  if ((n1 = read(fd1, buf, 20)) < 0) {
    printf("read error\n");
    exit(1);
  }
  printf("read %ld bytes\n", n1);
  printf("%s\n", buf);

  // 删除tmp.txt文件
  unlink("tmp.txt");

  return 0;
}