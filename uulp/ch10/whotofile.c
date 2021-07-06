#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int pid;

    printf("About to run who into a file\n");

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        int fd = open("userlist", O_CREAT | O_TRUNC | O_WRONLY, 0644);
        // int fd = creat("userlist", 0644);
        dup2(fd, 1);
        close(fd);
        execlp("who", "who", NULL);
        perror("execlp");
        exit(1);
    } else {
        wait(NULL);
        printf("Done running who. results in userlist\n");
    }
    return 0;
}