#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void f(int signum);

int main() {
    signal(SIGINT, f);
    for (int i = 0; i < 5; i++) {
        printf("num %d\n", i);
        sleep(1);
    }
}

void f(int signum) {
    printf("OUCH!\n");
}