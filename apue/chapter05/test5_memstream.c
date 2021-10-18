//
// Created by renxin on 2021/6/15.
//

#include "apue.h"

#define BSZ 48

int main() {
    char buf[BSZ];
    FILE *fp;
    if ((fp = fmemopen(buf, BSZ, "w+")) == NULL) {
        err_sys("fmemopen failed");
    }
    fprintf(fp, "hello, worldhello, worldhello, worldhello, worldhello, world");
    printf("before fflush: %s\n", buf);
    fflush(fp);
    printf("after fflush: %s\n", buf);

    if (fgetc(fp) == EOF)
        printf("EOF of memstream\n");

    printf("len of string in buf = %ld\n", (long)strlen(buf));
    return 0;
}