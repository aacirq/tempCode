//
// Created by renxin on 2021/6/11.
//

#include "apue.h"
#include <sys/stat.h>

int main(int argc, char **argv) {
    struct stat statBuf;
    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &statBuf) == -1) {
            err_ret("%s: stat error", argv[i]);
            continue;
        }
        printf("%s: dev = %d/%d", argv[i], major(statBuf.st_dev), minor(statBuf.st_dev));
        if (S_ISCHR(statBuf.st_mode) || S_ISBLK(statBuf.st_mode)) {
            printf(" (%s) rdev = %d/%d", S_ISCHR(statBuf.st_mode) ? "character" : "block", major(statBuf.st_rdev), minor(statBuf.st_rdev));
        }
        printf("\n");
    }
    return 0;
}