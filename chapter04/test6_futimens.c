//
// Created by renxin on 2021/6/11.
//

#include "apue.h"
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int fd;
    struct stat statBuf;
    struct timespec times[2];
    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &statBuf) == -1) {
            err_ret("%s: stat error", argv[i]);
            continue;
        }
        if ((fd = open(argv[i], O_TRUNC | O_RDWR)) == -1) {
            err_ret("%s: open error", argv[i]);
            continue;
        }
        times[0] = statBuf.st_atim;
        times[1] = statBuf.st_mtim;
        if (futimens(fd, times) == -1) {
            err_ret("%s: futimens error", argv[i]);
        }
        close(fd);
    }
    return 0;
}