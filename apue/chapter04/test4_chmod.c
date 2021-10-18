//
// Created by renxin on 2021/6/10.
//

#include "apue.h"
#include <sys/stat.h>

int main() {
    struct stat statBuf;

    if (stat("foo", &statBuf) == -1)
        err_sys("stat error for foo");
    if (chmod("foo", (statBuf.st_mode & ~S_IXGRP) | S_ISGID) == -1)
        err_sys("chmod error for foo");

    if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1)
        err_sys("chmod error for bar");
    return 0;
}