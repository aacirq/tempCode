#ifndef LIST_FILE_H
#define LIST_FILE_H

#include <cstdint>
#include <string>
#include <sys/stat.h>
#include <vector>

class ListFile {
private:
    typedef void (ListFile::*fun)(const char *, const struct stat &);

    uint64_t flags;
    std::vector<std::string> file_name;
    std::vector<std::string> dir_name;
    std::string mode_str;
    std::string name_str;

    fun print_fun;

    /**
     * FLAG元素对应的MUSK
     * ┌────┬─┬─┬─┬─┬─┬─┬─┬─┬─┐
     * │ ...│.│.│R│F│A│t│r│l│a│
     * └────┴─┴─┴─┴─┴─┴─┴─┴─┴─┘
     */
    static constexpr uint64_t MUSK_a = 1;
    static constexpr uint64_t MUSK_l = 1 << 1;
    static constexpr uint64_t MUSK_r = 1 << 2;
    static constexpr uint64_t MUSK_t = 1 << 3;
    static constexpr uint64_t MUSK_A = 1 << 4;
    static constexpr uint64_t MUSK_F = 1 << 5;
    static constexpr uint64_t MUSK_R = 1 << 6;

public:
    ListFile() : flags(0) {}

    /**
     * 根据p字符串中的字符设置FLAG
     * \return
     *    =0 (参数全部正确)
     *    >0 (错误参数index)
     */
    int set_flags(const char *p);

    /* 添加文件或文件夹 */
    void add_content(char *name);

    /* 输出所有内容 */
    void print();

private:
    /* 根据选项调整content，例如排序、去掉多余的选项等 */
    void adjust_content();

    /* 显示简单信息，没有-l选项 */
    void show_file_info_simple(const char *name, const struct stat &info);

    /* 显示详细信息，有-l选项 */
    void show_file_info_detail(const char *name, const struct stat &info);

    void print_file_name(const char *name, const struct stat &info);

    void print_a_dir(const std::string &name);

    /* 根据mode调整mode_str */
    void mode2letters(mode_t md);

    /* 获取id对应的名字 */
    void uid2name(uid_t id);

    void gid2name(gid_t id);

    /* 判定相应flag是否设置了 */
    bool is_set_flag_a() { return flags & MUSK_a; }

    bool is_set_flag_l() { return flags & MUSK_l; }

    bool is_set_flag_r() { return flags & MUSK_r; }

    bool is_set_flag_t() { return flags & MUSK_t; }

    bool is_set_flag_A() { return flags & MUSK_A; }

    bool is_set_flag_F() { return flags & MUSK_F; }

    bool is_set_flag_R() { return flags & MUSK_R; }
};

#endif
