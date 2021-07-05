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
 * @param var "var=value"形式的字符串
 * @return -1 - not a variable; 0 - OK
 */
int VLexport(const char *var);

/**
 * 增加/更新变量 name=value
 * @param name 变量名
 * @param value 变量值
 * @return 1 - if troble, 0 - if OK
 */
int VLstore(const char *name, const char *value);

/**
 * 取得var的值，深复制
 * @param var
 * @return address of copied variable
 */
char *VLlookup(const char *var);

/**
 * convert env to table of struct var
 * @param env environ tables to convert
 * @return 1 - ok; 0 - fail
 */
int VLenviron2table(char **env);

/**
 * Convert table(struct var *) to environ table
 * @return address of environ table(char **)
 */
char **VLtable2environ();

#endif //LEARNAPUE_VARLIB_H
