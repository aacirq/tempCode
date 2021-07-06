#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char line[100];

    fgets(line, 100, stdin);
    printf("%s", line);
    fgets(line, 100, stdin);
    printf("%s", line);
    fgets(line, 100, stdin);
    printf("%s", line);

    int fd = open("/etc/passwd", O_RDONLY);
    int newfd = dup2(fd, 0);
    if (newfd != 0) {
        fprintf(stderr, "Could not open data at fd 0\n");
        exit(1);
    }
    close(fd);

    fgets(line, 100, stdin);
    printf("%s", line);
    fgets(line, 100, stdin);
    printf("%s", line);
    fgets(line, 100, stdin);
    printf("%s", line);

    return 0;
}