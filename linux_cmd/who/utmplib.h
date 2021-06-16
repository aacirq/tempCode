#ifndef UTMPLIB_H
#define UTMPLIB_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>

#define NRECS 16
#define NULLUT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))

char utmp_buf[NRECS * UTSIZE];
int utmp_sz;
int utmp_ind;
int utmp_fd = -1;

int utmp_open(const char *filename) {
    utmp_fd = open(filename, O_RDONLY);
    utmp_sz = 0;
    utmp_ind = 0;
    return utmp_fd;
}

int utmp_reload() {
    ssize_t n_char = read(utmp_fd, utmp_buf, NRECS * UTSIZE);
    utmp_sz = n_char / UTSIZE;
    utmp_ind = 0;
    return utmp_sz;
}

struct utmp *utmp_next() {
    if (utmp_fd == -1)
        return NULLUT;
    if (utmp_ind == utmp_sz && utmp_reload() == 0)
        return NULLUT;

    char *rec = &utmp_buf[utmp_ind * UTSIZE];
    ++utmp_ind;
    return (struct utmp *) rec;
}

void utmp_close() {
    if (utmp_fd > 0)
        close(utmp_fd);
}

#endif
