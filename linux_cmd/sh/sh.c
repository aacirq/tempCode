//
// Created by renxin on 2021/6/16.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "sh.h"

char *next_cmd(const char *prompt, FILE *fp) {
    fprintf(stdout, "%s", prompt);
    int c;
    char *buf = NULL;
    size_t buf_size = 0;
    int pos = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (pos + 1 >= buf_size) {
            if (buf == NULL) {
                buf_size = BUFSIZ;
                buf = emalloc(sizeof(char) * buf_size);
            } else if (pos == buf_size) {
                buf_size += BUFSIZ;
                buf = erealloc(buf, sizeof(char) * buf_size);
            }
        }

        if (c == '\n')
            break;

        buf[pos++] = (char) c;
    }

    if ((buf == NULL) || (c == EOF && pos == 0))
        return NULL;
    buf[pos] = '\0';
    return buf;
}

static inline int is_delim(const char c) {
    return (c == ' ') || (c == '\t');
}

char **split_cmd(const char *cmd) {
    char **buf = emalloc(BUFSIZ);
    size_t buf_size = BUFSIZ;
    size_t buf_ind = 0;
    size_t spots = BUFSIZ / sizeof(char *);
    const char *p = cmd;
    while (*p != '\0') {
        while (is_delim(*p)) { p++; }
        if (*p == '\n')
            break;
        const char *pend = p;
        while (!is_delim(*pend) && *pend != '\0') {
            pend++;
        }
        if (buf_ind + 1 >= spots) {
            buf_size += BUFSIZ;
            buf = erealloc(buf, buf_size);
            spots = buf_size / sizeof(char *);
        }
        size_t cur_len = pend - p;
        char *p_str = emalloc(cur_len + 1);
        p_str[cur_len] = '\0';
        strncpy(p_str, p, cur_len);
        buf[buf_ind++] = p_str;
        p = pend;
    }
    buf[buf_ind] = NULL;
    return buf;
}

void execute(char *const argv[]) {
    int child_pid = fork();
    int st;
    if (child_pid == -1) {
        perror("fork error");
        exit(1);
    } else if (child_pid == 0) {
        execvp(argv[0], argv);
        perror("execvp failed");
        exit(1);
    } else {
        if (wait(&st) == -1) {
            perror("wait");
        }
    }
}

void freelist(char **arglist) {
    char **p = arglist;
    while (*p != NULL) {
        free(*p);
        p++;
    }
    free(arglist);
}

void *emalloc(size_t sz) {
    void *p = malloc(sz);
    if (p == NULL) {
        perror("no memory");
        exit(1);
    }
    return p;
}

void *erealloc(void *p, size_t sz) {
    p = realloc(p, sz);
    if (p == NULL) {
        perror("no memory");
        exit(1);
    }
    return p;
}