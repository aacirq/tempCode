# `ls`命令

支持的参数`ls [-alrAFR] [file/dir name]`

测试用例

- [x] `$ ls`
- [x] `$ ls ~/`
- [x] `$ ls ../ ../../ ../../ch02/who/Makefile`
- [x] `$ ls -a`
- [x] `$ ls -a ~/`
- [x] `$ ls -l`
- [x] `$ ls -l ~/`
- [x] `$ ls -r`
- [x] `$ ls -r ~/`
- [x] `$ ls -A`
- [x] `$ ls -A ~/`
- [x] `$ ls -F`
- [x] `$ ls -F ~/`
- [x] `$ ls -R`
- [x] `$ ls -R ../..`
- [x] `$ ls -rR ../..`
- [x] `$ ls -al`
- [x] `$ ls -al ~/`
- [x] `$ ls -lF /usr/bin/less*`
- [x] `$ ls -F /usr/bin/less*`


`-F`选项现在只有三种符号
`/`  文件夹
`*`  可执行文件
`@`  链接文件