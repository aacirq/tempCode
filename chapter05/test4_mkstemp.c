//
// Created by renxin on 2021/6/15.
//

#include "apue.h"
#include <sys/stat.h>
#include <errno.h>

int main() {
    int fd;
    char name_template[] = "/tmp/dirXXXXXX";
    if ((fd = mkstemp(name_template)) == -1)
        err_sys("mkstemp error");
    printf("temp name = %s\n", name_template);
    close(fd);

    struct stat statBuf;
    if (stat(name_template, &statBuf) == -1) {
        if (errno == ENOENT) {
            printf("file doesn't exist\n");
        } else {
            err_sys("stat failed");
        }
    } else {
        printf("file exist\n");
    }

    return 0;
}