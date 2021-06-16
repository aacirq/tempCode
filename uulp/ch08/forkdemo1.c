//
// Created by renxin on 2021/6/16.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("before: my pid is %d\n", getpid());

    int ret_from_fork = fork();
    sleep(1);

    printf("after: my pid is %d, fork() said %d\n", getpid(), ret_from_fork);
    exit(0);
}