.globl main
main:
    movq $SYS_exit, %rax
    movq $42, %rdi
    syscall
