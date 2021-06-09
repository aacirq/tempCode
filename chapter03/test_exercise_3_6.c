//
// Created by renxin on 2021/6/9.
//

#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";

int main() {
    // 产生test.txt文件
    int fd;
    if ((fd = creat("test.txt", FILE_MODE)) == -1) {
        err_quit("create error");
    }
    if (write(fd, buf1, 10) != 10) {
        err_quit("write error");
    }
    close(fd);

    // 处理
    if ((fd = open("test.txt", O_RDWR | O_APPEND)) == -1) {
        err_quit("open error");
    }
    char c;
    if (lseek(fd, 5, SEEK_SET) == -1) {
        err_quit("lseek error");
    }
    read(fd, &c, 1);
    // read: f
    printf("read: %c\n", c);

    // now offset = 6
    int cbuf = '2';
    write(fd, &cbuf, 1);

    return 0;
}