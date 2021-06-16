//
// Created by renxin on 2021/6/16.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXARGS 20
#define ARGLEN 100

char *make_arg(char *buf);
void execute(char * const argv[]);

int main() {
    int num_arg = 0;
    char arg_buf[ARGLEN];
    char *arg_list[MAXARGS];

    while (num_arg < MAXARGS) {
        printf("Args[%d]: ", num_arg);
        if (fgets(arg_buf, ARGLEN, stdin) != NULL && arg_buf[0] != '\n') {
            arg_list[num_arg] = make_arg(arg_buf);
            num_arg++;
        } else {
            break;
        }
    }

    if (num_arg > 0) {
        arg_list[num_arg++] = NULL;
        execute(arg_list);
    }
    return 0;
}

/* 从buf复制一份出来 */
char *make_arg(char *buf) {
    size_t len = strlen(buf);
    buf[len - 1] = '\0'; // 去掉后面的'\n'符号
    char *res = malloc(sizeof(char) * (len + 1));
    if (res == NULL) {
        fprintf(stderr, "no memory\n");
        exit(1);
    }
    strcpy(res, buf);
    return res;
}

/* 执行程序 */
void execute(char * const argv[]) {
    execvp(argv[0], argv);
    perror("execvp failed");
    exit(1);
}
