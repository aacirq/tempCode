//
// Created by renxin on 2021/6/16.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("Before: my pid is %d\n", getpid());
    int ret_fork = fork();
    if (ret_fork == -1) {
        perror("fork error");
    } else if (ret_fork == 0) {
        printf("I am child, my pid is %d\n", getpid());
    } else {
        printf("I am parent, my pid is %d\n", getpid());
    }
    exit(0);
}