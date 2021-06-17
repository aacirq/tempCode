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
 * 执行shell命令
 * @param arglist 参数列表
 */
void execute(char *const *arglist);

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
