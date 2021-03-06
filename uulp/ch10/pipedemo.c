#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int apipe[2];
    char buf[BUFSIZ];

    if (pipe(apipe) == -1) {
        perror("can not make pipe");
        exit(1);
    }

    printf("Got a pipe! It is file descriptors: {%d, %d}\n", 
            apipe[0], apipe[1]);

    while (fgets(buf, BUFSIZ, stdin)) {
        int len = strlen(buf);
        if (write(apipe[1], buf, len) != len) {
            perror("writing to pipe");
            break;
        }
        for (int i = 0; i < BUFSIZ; i++) {
            buf[i] = 'X';
        }
        len = read(apipe[0], buf, BUFSIZ);
        if (len == -1) {
            perror("reading from pipe");
            break;
        }
        if (write(STDOUT_FILENO, buf, len) != len) {
            perror("writing to stdout");
            break;
        }
    }

    return 0;
}