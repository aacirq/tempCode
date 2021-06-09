//
// Created by renxin on 2021/6/9.
// 验证O_APPEND的效果
// 结论：如果一个偏移量offset不在文件（设置了O_APPEND）结尾，write的时候，会首先设置offset到文件结尾处。
//

#include "apue.h"

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main() {
    int fd;
    if ((fd = creat("test.txt", FILE_MODE)) == -1) {
        err_sys("create error");
    }
    if (write(fd, buf1, 10) != 10) {
        err_sys("write error");
    }
    close(fd);

    if ((fd = open("test.txt", O_RDWR | O_APPEND)) == -1) {
        err_sys("create error");
    }
    if (lseek(fd, 0, SEEK_SET) == -1) {
        err_sys("seek error");
    }
    if (write(fd, buf2, 10) != 10) {
        err_sys("write error");
    }
    close(fd);

    return 0;
}