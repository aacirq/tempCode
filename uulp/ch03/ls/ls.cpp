#include "list_file.h"
#include <iostream>

using std::cerr;
using std::endl;

int main(int argc, char *argv[]) {
    ListFile ls;

    bool empty_content = true;

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            int error_ind;
            if ((error_ind = ls.set_flags(&argv[i][0])) > 0) {
                // 参数错误
                cerr << "ls: invalid option " << argv[i][error_ind] << endl;
                exit(1);
            }
        } else {
            empty_content = false;
            ls.add_content(&argv[i][0]);
        }
    }

    // 没有指定文件，默认当前文件夹
    if (empty_content) {
        char cur_dir[] = ".";
        ls.add_content(cur_dir);
    }

    // 输出信息
    ls.print();

    exit(0);
}