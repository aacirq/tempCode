//
// Created by renxin on 2021/5/26.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

ino_t get_ino(const char *fname);

void printPathTo(ino_t inum);

int main(int argc, char *argv[]) {
    ino_t cur_name = get_ino(".");
    printPathTo(cur_name);
    putchar('\n');
    return 0;
}

/**
 * (在进程所在工作目录下)通过i节点编号获得文件名字符串
 * @param inum i节点编号
 * @param namebuf 保存文件名的缓存区
 * @param buflen 缓存区长度
 */
void ino2name(ino_t inum, char *namebuf, int buflen) {
    DIR *this_dir = opendir(".");

    if (this_dir == nullptr) {
        perror(".");
        exit(1);
    }

    struct dirent *cur_dirent = nullptr;

    while ((cur_dirent = readdir(this_dir)) != nullptr) {
        if (cur_dirent->d_ino == inum) {
            strncpy(namebuf, cur_dirent->d_name, buflen);
            namebuf[buflen - 1] = '\0';
            closedir(this_dir);
            return;
        }
    }

    fprintf(stderr, "error looking for ino %ld\n", inum);
    exit(1);
}

/**
 * 打印从根目录到i节点编号表示目录的路径
 * @param inum
 */
void printPathTo(ino_t inum) {
    char name[BUFSIZ];

    ino_t parent_ino = get_ino("..");
    if (parent_ino == inum) {
        return;
    }

    chdir("..");

    ino2name(inum, name, BUFSIZ);

    printPathTo(parent_ino);

    printf("/%s", name);
}

/**
 * （在进程当前工作目录下）从文件名得到文件的i节点编号
 * @param fname 文件名
 * @return i节点编号
 */
ino_t get_ino(const char *fname) {
    struct stat statbuf;

    if (stat(fname, &statbuf) == -1) {
        fprintf(stderr, "can not stat ");
        perror(fname);
        exit(1);
    }

    return statbuf.st_ino;
}
