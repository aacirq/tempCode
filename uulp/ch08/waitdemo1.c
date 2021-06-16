//
// Created by renxin on 2021/6/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void child_code(int second);
void parent_code(int childpid);

int main() {
    printf("Before: my pid is %d\n", getpid());
    int ret_fork = fork();
    if (ret_fork == -1) {
        perror("fork error");
    } else if (ret_fork == 0) {
        child_code(5);
    } else {
        parent_code(ret_fork);
    }
}

void child_code(int second) {
    printf("child %d here. will sleep for %d seconds\n", getpid(), second);
    sleep(second);
    printf("child done. about to exit\n");
    exit(17);
}

void parent_code(int childpid) {
    int st;
    int ret_wait = wait(&st);
    printf("do wait for %d, wait returned %d\n", childpid, ret_wait);

    int high8 = st >> 8;
    int low7 = st & 0x7F;
    int bit7 = st & 0x80;
    printf("status: exit = %d, sig = %d, core = %d\n", high8, low7, bit7);
}