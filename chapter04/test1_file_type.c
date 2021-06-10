//
// Created by renxin on 2021/6/10.
//

#include "apue.h"
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    struct stat statBuf;
    char *ptr;
    for (int i = 1; i < argc; i++) {
        printf("%s: ", argv[i]);
        if (lstat(argv[i], &statBuf) == -1) {
            err_ret("lstat error");
            continue;
        }
        if (S_ISREG(statBuf.st_mode))
            printf("regular\n");
        else if (S_ISDIR(statBuf.st_mode))
            printf("directory\n");
        else if (S_ISCHR(statBuf.st_mode))
            printf("character special\n");
        else if (S_ISBLK(statBuf.st_mode))
            printf("block special\n");
        else if (S_ISFIFO(statBuf.st_mode))
            printf("fifo\n");
        else if (S_ISLNK(statBuf.st_mode))
            printf("symbolic link\n");
        else if (S_ISSOCK(statBuf.st_mode))
            printf("socket\n");
        else
            printf("** unknown mode **\n");
    }
    return 0;
}