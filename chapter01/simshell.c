#include "apue.h"
#include <sys/wait.h>

static void sig_int(int);

int main() {
    char buf[MAXLINE];
    pid_t pid;
    int buf_len;
    int status;

    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal error");

    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        buf_len = strlen(buf);
        if (buf_len == 1) {
            printf("%% ");
            continue;
        }

        if (buf[buf_len - 1] == '\n')
            buf[buf_len - 1] = '\0';

        if ((pid = fork()) < 0) {
            printf("for error\n");
        } else if (pid == 0) { /* child */
            execlp(buf, buf, (char *) 0);
            err_ret("couldn't execute: %s\n", buf);
            exit(127);
        }

        /* parent */
        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        printf("%% ");
    }

    exit(0);
}

static void sig_int(int signo) {
    printf("interrupt\n%% ");
    fflush(stdout);
}