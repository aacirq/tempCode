#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  char q[] = "Do you wanna build a C99 program?";
#define or "go debugging with gdb?"
  static unsigned int i = sizeof(or) != strlen(or);
  char *ptr = "lathe";
  size_t come = fprintf(stdout, "%s door", ptr + 2);
  int away = !(int)*"";
  int *shared = mmap(NULL, sizeof(int *), PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  munmap(shared, sizeof(int *));
  if (!fork()) {
    execlp("man", "man", "-3", "ftell", (char *)0);
    perror("failed");
  }
  if (!fork()) {
    execlp("make", "make", "snowman", (char *)0);
    execlp("make", "make", (char *)0);
  }
  exit(0);
}