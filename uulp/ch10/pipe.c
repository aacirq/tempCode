#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "usage: pipe <command> <command>");
        exit(1);
    }

    int apipe[2];
    if (pipe(apipe) == -1) {
        perror("could not make pipe");
        exit(1);
    }

    int pid = fork();
    if (pid == -1) {
        perror("can not fork");
        exit(1);
    }

    if (pid > 0) {
        close(apipe[1]);
        if (dup2(apipe[0], STDIN_FILENO) == -1) {
            perror("parent: can not dup2");
            exit(1);
        }
        close(apipe[0]);
        execlp(argv[2], argv[2], NULL);
        perror(argv[2]);
        exit(4);
    } else {
        close(apipe[0]);
        if (dup2(apipe[1], STDOUT_FILENO) == -1) {
            perror("child: can not dup2");
            exit(1);
        }
        close(apipe[1]);
        execlp(argv[1], argv[1], NULL);
        perror(argv[1]);
        exit(5);
    }

    return 0;
}