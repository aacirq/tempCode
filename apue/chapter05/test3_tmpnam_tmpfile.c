//
// Created by renxin on 2021/6/15.
//

#include "apue.h"

int main() {
    printf("%s\n", tmpnam(NULL));

    char name[L_tmpnam];
    tmpnam(name);
    printf("%s\n", name);

    FILE *fp;
    if ((fp = tmpfile()) == NULL)
        err_sys("tmpfile error");

    fputs("one line of output\n", fp);
    rewind(fp);
    char line[MAXLINE];
    if (fgets(line, MAXLINE, fp) == NULL)
        err_sys("fgets error");
    fputs(line, stdout);

    return 0;
}