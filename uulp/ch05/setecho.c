//
// Created by renxin on 2021/6/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#define oops(str, i) \
    do {             \
        perror(str); \
        exit(i);     \
    } while (0)

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: setecho <y/n>");
        exit(1);
    }

    struct termios info;
    if (tcgetattr(0, &info) == -1) {
        oops("tcgetattr error", 1);
    }
    if (argv[1][0] == 'y') {
        info.c_lflag |= ECHO;
    } else {
        info.c_lflag &= ~ECHO;
    }

    if (tcsetattr(0, TCSANOW, &info) == -1) {
        oops("tcsetattr error", 1);
    }
    exit(0);
}