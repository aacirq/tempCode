//
// Created by renxin on 2021/6/21.
//

#ifndef LEARNAPUE_VARLIB_H
#define LEARNAPUE_VARLIB_H

struct var {
    char *str;
    int global;
};

#ifndef MAXVARS
#define MAXVARS 4096
#endif

static struct var table[MAXVARS];

/**
 * list all variables
 */
void VLlist();

/**
 * 全局化
 * 将变量添加到环境中，如果str中的变量名部分是一个局部变量，那么把它添加到环境中，如果str中的变量名不存在，那么新建一个环境
 * @param str "var=value"形式的字符串
 * @return
 */
int VLexport(const char *str);

/**
 * 增加/更新变量 name=value
 * @param name 变量名
 * @param value 变量值
 * @return 1 - if troble, 0 - if OK
 */
int VLstore(const char *name, const char *value);

/**
 * 取得var的值
 * @param var
 * @return
 */
char *VLlookup(const char *var);

#endif //LEARNAPUE_VARLIB_H
