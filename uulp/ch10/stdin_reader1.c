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

    close(0);

    int fd = open("/etc/passwd", O_RDONLY);
    if (fd != 0) {
        fprintf(stderr, "Could not open data at fd 0\n");
        exit(1);
    }

    fgets(line, 100, stdin);
    printf("%s", line);
    fgets(line, 100, stdin);
    printf("%s", line);
    fgets(line, 100, stdin);
    printf("%s", line);

    return 0;
}