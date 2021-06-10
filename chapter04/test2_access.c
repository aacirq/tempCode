//
// Created by renxin on 2021/6/10.
//

#include "apue.h"
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    if (argc != 2)
        err_quit("usage: a.out <pathname>");
    if (access(argv[1], R_OK) == -1) {
        err_ret("access error for %s", argv[1]);
    } else {
        printf("read access OK\n");
    }

    if (open(argv[1], O_RDONLY) < 0) {
        err_ret("open error for %s", argv[1]);
    } else {
        printf("open for reading OK\n");
    }
    return 0;
}