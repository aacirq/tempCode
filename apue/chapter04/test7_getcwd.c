//
// Created by renxin on 2021/6/11.
//

#include "apue.h"

int main() {
    char buf[4096];

    if (getcwd(buf, 4096) == NULL) {
        err_sys("getcwd failed");
    }
    printf("cwd = %s\n", buf);
    return 0;
}