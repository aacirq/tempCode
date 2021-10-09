# 文件I/O

<unistd.h>: STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO

(文件描述符，整型类型)

<stdio.h>: stdin, stdout, stderr

(标准文件IO流，FILE结构类型)


## 文件操作流程

  - 打开文件，获取文件描述符（open）
  - 改变文件位置（lseek）
  - 读写(read, write)
  - 关闭描述符（显示、隐式）(close)


## 文件类型

  - 普通文件
    - 文本文件
    - 二进制文件
  - 目录
  - socket文件


## 系统IO

- 读写普通文件：
    open, read, write, close

- 读写文件元数据：
    stat，fstat

- 操作目录：
    opendir, readdir, closedir

- 重定向：
    dup2


## 标准IO

有缓冲，输出的时候可能不会立即输出，只保存在缓冲区

不适合用于socket的文件描述符
