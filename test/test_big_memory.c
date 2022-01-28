#include <stdio.h>
#include <stdlib.h>

int main() {
  // long long sz = 0x40000000;
  // size_t sz = 10 << 30;
  // size_t sz = 0x280000000L;
  size_t sz = 1 << 30;
  printf("sz = %lx\n", sz * 8);
  void *p = malloc(sz * 8);
  printf("%p\n", p);

  printf("sz = %lx\n", sz * 8);
  p = malloc(sz * 8);
  printf("%p\n", p);

  printf("sz = %lx\n", sz * 10);
  p = malloc(sz * 12);
  printf("%p\n", p);
  return 0;
}