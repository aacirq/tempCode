#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <utmp.h>

#include "utmplib.h"

#define SHOWHOST

void show_utmp(struct utmp *record);

void show_time(int32_t time);

int main() {
    int utmpfd;

    if ((utmpfd = utmp_open(UTMP_FILE)) == -1) {
        perror(UTMP_FILE);
        exit(1);
    }

    struct utmp *cur_record;

    while ((cur_record = utmp_next()) != NULLUT)
        show_utmp(cur_record);

    utmp_close();
    exit(0);
}

void show_utmp(struct utmp *u) {
    if (u->ut_type != USER_PROCESS)
        return;
    printf("%-8.8s", u->ut_user);
    printf(" ");
    printf("%-8.8s", u->ut_line);
    printf(" ");

    show_time(u->ut_tv.tv_sec);
    printf(" ");
#ifdef SHOWHOST
    printf("(%s)", u->ut_host);
#endif
    printf("\n");
}

void show_time(int32_t time) {
    time_t t = time;
    char time_str[17];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M", localtime(&t));
    printf("%s", time_str);

    // 这种也可以，但是这种显示格式和我的系统(Ubuntu 18.04)中的who有点区别
    // char *p;
    // time_t t = time;
    // p = ctime(&t);
    // printf("%12.12s", p + 4);
}