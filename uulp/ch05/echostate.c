//
// Created by renxin on 2021/6/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

int main() {
    struct termios info;
    if (tcgetattr(0, &info) == -1) {
        perror("tcgetattr error");
        exit(1);
    }

    if (info.c_lflag & ECHO) {
        printf("echo is on\n");
    } else {
        printf("echo is off\n");
    }

    return 0;
}