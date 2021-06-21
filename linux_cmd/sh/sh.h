//
// Created by renxin on 2021/6/17.
//

#ifndef LEARNAPUE_SH_H
#define LEARNAPUE_SH_H

/**
 * 读取一行命令
 * @param prompt 打印的提示符
 * @param fp 输入流
 * @return 读取到的字符串首地址，或者NULL - EOF or error
 */
char *next_cmd(const char *prompt, FILE *fp);

/**
 * 将一行命令划分成参数列表
 * @param cmd 读取的命令行字符串
 * @return 以NULL结尾的参数列表
 */
char **split_cmd(const char *cmd);

/**
 * process user command
 * @param arglist 读取的参数列表
 * @return result of processing command
 *         0 - success, -1 - problem happened
 */
int process(char *const *arglist);

/**
 * 判定是否是shell脚本的内容，例如if, then, else, fi这些
 * @param arg 参数，用于判定是否为脚本内容
 * @return 1-脚本内容，0-命令
 */
int is_control_command(const char *arg);

/**
 * 处理脚本内容，执行
 * @param arglist 参数列表
 * @return 0 - 执行成功，-1 - 执行失败，语法错误
 */
int do_control_command(char *const *arglist);

/**
 * 判定这条命令是否能执行，还是应该跳过
 * @param arglist 参数列表
 * @return 1 - 可以执行，0 - 跳过
 */
int ok_to_execute(char *const *arglist);

/**
 * 出现错误，打印输出信息，调整区域为中立区
 * @param msg 错误提示信息
 * @return -1
 */
int syn_err(const char *msg);

/**
 * 执行shell命令
 * @param arglist 参数列表
 * @return 0 - 执行成功，-1 - 失败
 */
int execute(char *const *arglist);

/**
 * 释放参数列表（包括列表本身）
 * @param arglist 参数列表首地址
 */
void freelist(char **arglist);

/**
 * 进行错误处理的malloc()，如果有错误发生，exit
 * @param sz 字节数
 * @return 申请内存的首地址
 */
void *emalloc(size_t sz);

/**
 * 有错误处理的realloc()，如果有错误发生，exit
 * @param p
 * @param sz
 * @return 申请内存的首地址
 */
void *erealloc(void *p, size_t sz);

#endif //LEARNAPUE_SH_H
