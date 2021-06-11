//
// Created by renxin on 2021/6/11.
//

#include "apue.h"
#include <fcntl.h>

int main() {
    if (open("tempfile", O_RDWR) == -1) {
        err_sys("open error");
    }
    if (unlink("tempfile") == -1) {
        err_sys("unlink error");
    }
    printf("file unlinked\n");
    sleep(15);
    printf("done\n");
    return 0;
}