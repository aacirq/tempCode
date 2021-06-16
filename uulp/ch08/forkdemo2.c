//
// Created by renxin on 2021/6/16.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("before: my pid is %d\n", getpid());
    fork();
    fork();
    fork();
    printf("after: my pid is %d\n", getpid());
    exit(0);
}