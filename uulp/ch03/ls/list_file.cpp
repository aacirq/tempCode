#include "list_file.h"
#include <algorithm>
#include <cstring>
#include <dirent.h>
#include <grp.h>
#include <iostream>
#include <map>
#include <pwd.h>
#include <unistd.h>

int ListFile::set_flags(const char *p) {
    const char *origin_p = p;
    while (*(++p) != '\0') {
        switch (*p) {
            case 'a':
                flags |= MUSK_a;
                break;

            case 'l':
                flags |= MUSK_l;
                break;

            case 'r':
                flags |= MUSK_r;
                break;

            case 't':
                flags |= MUSK_t;
                break;

            case 'A':
                flags |= MUSK_A;
                break;

            case 'F':
                flags |= MUSK_F;
                break;

            case 'R':
                flags |= MUSK_R;
                break;

            default:
                return p - origin_p;
                break;
        }
    }
    return 0;
}

void ListFile::add_content(char *name) {
    struct stat statbuf;
    if (stat(name, &statbuf) == -1)
        perror(name);

    // 添加
    if (S_ISDIR(statbuf.st_mode)) {
        dir_name.push_back(name);
    } else {
        file_name.push_back(name);
    }
}

struct StrCmpNoCase {
    bool operator()(const std::string &s1, const std::string &s2) const {
        // linux下的ls排序方式不清楚，现在是按字母排序（不区分大小写）
        std::string str1 = s1;
        std::string str2 = s2;
        std::transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
        std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
        return str1 < str2;
    }
};

void ListFile::print() {
    adjust_content();

    struct stat statbuf;

    // 输出文件
    if (!file_name.empty()) {
        for (auto name : file_name) {
            lstat(name.c_str(), &statbuf);
            (this->*(this->print_fun))(name.c_str(), statbuf); // TODO 这个用法不太懂
        }
        if (!is_set_flag_l())
            printf("\n");
    }

    // 输出文件夹中的内容
    if (!dir_name.empty()) {
        for (auto itr = dir_name.begin(); itr != dir_name.end(); ++itr) {
            if (!file_name.empty() || itr != dir_name.begin()) {
                std::cout << std::endl;
            }
            if ((!file_name.empty() || dir_name.size() > 1) || is_set_flag_R()) {
                std::cout << *itr << ":" << std::endl;
            }

            print_a_dir(*itr);
            if (!is_set_flag_l())
                printf("\n");
        }
    }
}

void ListFile::adjust_content() {
    // 设置输出方式
    if (is_set_flag_l()) {
        print_fun = &ListFile::show_file_info_detail;
    } else {
        print_fun = &ListFile::show_file_info_simple;
    }

    // 排序
    std::sort(file_name.begin(), file_name.end());
    std::sort(dir_name.begin(), dir_name.end());
}

void ListFile::show_file_info_simple(const char *name,
                                     const struct stat &info) {
    print_file_name(name, info);
    printf("  ");
}

void ListFile::show_file_info_detail(const char *name,
                                     const struct stat &info) {
    mode2letters(info.st_mode);

    time_t mt = info.st_mtim.tv_sec;

    // output
    std::cout << mode_str << " ";
    printf("%ld ", info.st_nlink);
    uid2name(info.st_uid);
    printf("%-8s ", name_str.c_str());
    gid2name(info.st_gid);
    printf("%-8s ", name_str.c_str());
    printf("%8ld ", info.st_size);
    printf("%.12s ", ctime(&mt) + 4);
    print_file_name(name, info);
    printf("\n");
}

void ListFile::print_file_name(const char *name, const struct stat &info) {
    printf("%s", name);
    if (is_set_flag_F()) {
        // 设置文件后的符号
        if (S_ISDIR(info.st_mode)) {
            printf("/");
        } else if (S_ISLNK(info.st_mode)) {
            if (is_set_flag_l()) {
                printf(" -> ");
                // 输出链接目标文件
                static char name_buf[4096];
                int name_n = 0;
                if ((name_n = readlink(name, name_buf, 4096)) == -1) {
                    perror(name);
                }
                name_buf[name_n] = '\0';

                // 链接目标
                struct stat statbuf;
                stat(name, &statbuf);
                print_file_name(name_buf, statbuf);
            } else {
                printf("@");
            }
        } else if (info.st_mode & S_IXUSR || info.st_mode & S_IXGRP ||
                   info.st_mode & S_IXOTH) {
            printf("*");
        }
    }
}

void ListFile::print_a_dir(const std::string &name) {
    // 打开文件夹
    DIR *cur_dir;
    struct dirent *cur_dirent;
    struct stat statbuf;

    std::map<std::string, struct stat, StrCmpNoCase> name_table;

    cur_dir = opendir(name.c_str());
    if (cur_dir == nullptr) {
        perror(name.c_str());
        return;
    }

    // 计算total值大小
    long int total = 0;
    while ((cur_dirent = readdir(cur_dir)) != nullptr) {
        // 筛选
        if (cur_dirent->d_name[0] == '.') {
            if (!is_set_flag_a() && !is_set_flag_A())
                continue;
            if (is_set_flag_A()) {
                if (strcmp(cur_dirent->d_name, ".") == 0 ||
                    strcmp(cur_dirent->d_name, "..") == 0)
                    continue;
            }
        }

        stat((name + "/" + cur_dirent->d_name).c_str(), &statbuf);
        total += statbuf.st_size / statbuf.st_blksize +
                 (statbuf.st_size % statbuf.st_blksize > 0);
        name_table.insert({std::string(cur_dirent->d_name), statbuf});
    }
    closedir(cur_dir);

    if (is_set_flag_l()) {
        printf("total %ld\n", total * statbuf.st_blksize / 1024);
    }

    if (is_set_flag_r()) {
        for (auto rit = name_table.rbegin(); rit != name_table.rend(); ++rit) {
            (this->*(this->print_fun))(rit->first.c_str(), rit->second);
        }
    } else {
        for (auto itr = name_table.begin(); itr != name_table.end(); ++itr) {
            (this->*(this->print_fun))(itr->first.c_str(), itr->second);
        }
    }

    // 设置-R选项后，迭代输出文件夹
    if (is_set_flag_R()) {
        if (is_set_flag_r()) {
            for (auto rit = name_table.rbegin(); rit != name_table.rend(); ++rit) {
                if (S_ISDIR(rit->second.st_mode)) {
                    std::cout << std::endl
                              << std::endl
                              << name + "/" + rit->first << ":" << std::endl;
                    print_a_dir(name + "/" + rit->first);
                }
            }
        } else {
            for (auto itr = name_table.begin(); itr != name_table.end(); ++itr) {
                if (S_ISDIR(itr->second.st_mode)) {
                    std::cout << std::endl
                              << std::endl
                              << name + "/" + itr->first << ":" << std::endl;
                    print_a_dir(name + "/" + itr->first);
                }
            }
        }
    }
}

void ListFile::mode2letters(mode_t md) {
    mode_str.assign("----------");
    mode_str.resize(11);
    if (S_ISDIR(md))
        mode_str[0] = 'd';
    if (S_ISCHR(md))
        mode_str[0] = 'c';
    if (S_ISBLK(md))
        mode_str[0] = 'b';
    if (S_ISLNK(md))
        mode_str[0] = 'l';

    // user
    if (md & S_IRUSR)
        mode_str[1] = 'r';
    if (md & S_IWUSR)
        mode_str[2] = 'w';
    if (md & S_IXUSR)
        mode_str[3] = 'x';

    // group
    if (md & S_IRGRP)
        mode_str[4] = 'r';
    if (md & S_IWGRP)
        mode_str[5] = 'w';
    if (md & S_IXGRP)
        mode_str[6] = 'x';

    // other
    if (md & S_IROTH)
        mode_str[7] = 'r';
    if (md & S_IWOTH)
        mode_str[8] = 'w';
    if (md & S_IXOTH)
        mode_str[9] = 'x';
}

inline void ListFile::uid2name(uid_t id) {
    struct passwd *pw;

    if ((pw = getpwuid(id)) == NULL) {
        name_str = std::to_string(id);
    } else {
        name_str = pw->pw_name;
    }
}

inline void ListFile::gid2name(gid_t id) {
    struct group *gr;

    if ((gr = getgrgid(id)) == NULL) {
        name_str = std::to_string(id);
    } else {
        name_str = gr->gr_name;
    }
}
