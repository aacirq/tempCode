//
// Created by renxin on 2021/6/17.
//

#include <stdio.h>
#include <stdlib.h>

#include "sh.h"

int main() {
    char *cmd_str = NULL;
    char **arglist = NULL;
    char prompt[] = "> ";

    while ((cmd_str = next_cmd(prompt, stdin)) != NULL) {
        if ((arglist = split_cmd(cmd_str)) != NULL) {
            execute(arglist);
            freelist(arglist);
        }
        free(cmd_str);
    }

    return 0;
}
