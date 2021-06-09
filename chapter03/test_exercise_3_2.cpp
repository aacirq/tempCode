//
// Created by renxin on 2021/6/9.
//

#include "apue.h"
#include <list>

using std::list;

int my_dup2(int fd, int fd2) {
    if (fd == fd2)
        return fd2;
    close(fd2);

    list<int> fd_list;
    int tmp_fd;
    while ((tmp_fd = dup(fd)) != fd2) {
        printf("create fd %d\n", tmp_fd);
        fd_list.push_back(tmp_fd);
    }
    for (int & itr : fd_list) {
        close(itr);
        printf("close fd %d\n", itr);
    }
    return fd2;
}

int main() {
    int fd = my_dup2(STDOUT_FILENO, 15);
    write(15, "write from fd 15\n", 17);
    return 0;
}