//
// Created by renxin on 2021/6/9.
//

#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";

int main() {
    int fd;
    if ((fd = creat("test.txt", FILE_MODE)) == -1) {
        err_sys("create error");
    }
    if (write(fd, buf1, 10) != 10) {
        err_sys("write error");
    }
    close(fd);

    int fd1, fd2;
    if ((fd1 = open("test.txt", O_RDONLY)) == -1 || (fd2 = open("test.txt", O_RDONLY)) == -1) {
        err_sys("read error");
    }
    if (lseek(fd1, 0, SEEK_SET) == -1 || lseek(fd2, 5, SEEK_SET) == -1) {
        err_sys("lseek error");
    }
    char c1, c2;
    read(fd1, &c1, 1);
    read(fd2, &c2, 1);
    printf("c1: %c, c2: %c\n", c1, c2);
    return 0;
}