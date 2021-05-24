#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 4096
#define MAXLINE 4096
#define COPYMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)

void err_doit(int flag, int error_num, const char *format, va_list ap);

void err_sys(const char *format, ...);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s <src-file> <dst-file>\n", argv[0]);
        exit(1);
    }

    int src_fd;
    if ((src_fd = open(argv[1], O_RDONLY)) == -1)
        err_sys("can not open <%s>", argv[1]);

    int dst_fd;
    if ((dst_fd = creat(argv[2], COPYMODE)) == -1)
        err_sys("can not create <%s>", argv[2]);

    char buffer[BUFSIZE];
    int n;
    while ((n = read(src_fd, buffer, BUFSIZE)) > 0) {
        if (write(dst_fd, buffer, n) != n)
            err_sys("write error");
    }

    if (n == -1)
        err_sys("read error from %s", argv[1]);

    if (close(src_fd) == -1 || close(dst_fd) == -1)
        err_sys("closing files error");

    exit(0);
}

void err_sys(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    err_doit(1, errno, format, ap);
    va_end(ap);
    exit(1);
}

void err_doit(int flag, int error_num, const char *format, va_list ap) {
    char buf[MAXLINE];
    int n = vsnprintf(buf, MAXLINE, format, ap);
    if (flag) {
        snprintf(buf + n, MAXLINE - n, ": %s", strerror(error_num));
    }
    strcat(buf, "\n");
    fflush(stdout);
    fputs(buf, stderr);
    fflush(NULL);
}
