#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

void do_ls(const char *dir_name);

void do_stat(const char *, int);

void show_file_info(const char *filename, struct stat *info, int offset);

void mode2letters(mode_t, char *);

char *uid2name(uid_t);

char *gid2name(gid_t);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        do_ls(".");
    } else {
        while (--argc != 0) {
            printf("%s:\n", *(++argv));
            do_ls(*argv);
        }
    }
    exit(0);
}

#define NAME_LENGTH 4096

void do_ls(const char *dir_name) {
    DIR *dir;

    if ((dir = opendir(dir_name)) == NULL) {
        fprintf(stderr, "ls: can not open %s\n", dir_name);
    } else {
        struct dirent *cur;

        static char name_str[NAME_LENGTH];
        strcpy(name_str, dir_name);
        int n = strlen(dir_name);
        if (name_str[n - 1] != '/') {
            name_str[n] = '/';
            ++n;
        }

        while ((cur = readdir(dir)) != NULL) {
            strcpy(name_str + n, cur->d_name);
            do_stat(name_str, n);
        }
        closedir(dir);
    }
}

void do_stat(const char *filename, int offset) {
    struct stat statbuf;

    if (stat(filename, &statbuf) == -1) {
        perror(filename);
    } else {
        show_file_info(filename, &statbuf, offset);
    }
}

void show_file_info(const char *filename, struct stat *info, int offset) {
    // mode
    static char mode_str[11];
    mode2letters(info->st_mode, mode_str);

    // time convert
    time_t mt = info->st_mtim.tv_sec;

    // output
    printf("%s ", mode_str);
    printf("%ld ", info->st_nlink);
    printf("%-8s ", uid2name(info->st_uid));
    printf("%-8s ", gid2name(info->st_gid));
    printf("%8ld ", info->st_size);
    printf("%.12s ", ctime(&mt) + 4);
    printf("%s", filename + offset);
    if (S_ISDIR(info->st_mode))
        printf("/");
    printf("\n");
}

void mode2letters(mode_t md, char *str) {
    strcpy(str, "----------");
    if (S_ISDIR(md))
        str[0] = 'd';
    if (S_ISCHR(md))
        str[0] = 'c';
    if (S_ISBLK(md))
        str[0] = 'b';

    // user
    if (md & S_IRUSR)
        str[1] = 'r';
    if (md & S_IWUSR)
        str[2] = 'w';
    if (md & S_IXUSR)
        str[3] = 'x';

    // group
    if (md & S_IRGRP)
        str[4] = 'r';
    if (md & S_IWGRP)
        str[5] = 'w';
    if (md & S_IXGRP)
        str[6] = 'x';

    // other
    if (md & S_IROTH)
        str[7] = 'r';
    if (md & S_IWOTH)
        str[8] = 'w';
    if (md & S_IXOTH)
        str[9] = 'x';
}

char *uid2name(uid_t id) {
    struct passwd *pw;
    static char numstr[10];

    if ((pw = getpwuid(id)) == NULL) {
        sprintf(numstr, "%d", id);
        return numstr;
    } else {
        return pw->pw_name;
    }
}

char *gid2name(gid_t id) {
    struct group *gr;
    static char numstr[10];

    if ((gr = getgrgid(id)) == NULL) {
        sprintf(numstr, "%d", id);
        return numstr;
    } else {
        return gr->gr_name;
    }
}
