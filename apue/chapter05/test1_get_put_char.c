//
// Created by renxin on 2021/6/15.
//

#include "apue.h"

int main() {
    int c;
    while ((c = fgetc(stdin)) != EOF)
        if (fputc(c, stdout) == EOF)
            err_sys("output error");

    if (ferror(stdin))
        err_sys("input error");

    return 0;
}