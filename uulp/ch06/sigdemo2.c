#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    signal(SIGINT, SIG_IGN);
    while (1) {
        printf("go on\n");
        sleep(1);
    }
}
