#ifndef _APUE_H
#define _APUE_H

#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 4096 /* max line length */

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

void err_quit(const char *, ...) __attribute__((noreturn));
void err_sys(const char *, ...) __attribute__((noreturn));
void err_ret(const char *, ...);
void err_dump(const char *, ...) __attribute__((noreturn));

char *path_alloc(size_t *sizep);

#endif /* _APUE_H */