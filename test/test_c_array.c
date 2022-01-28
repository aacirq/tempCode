/**
 * 测试c语言中数组和结构体的指定初始化
 */
#include <stdio.h>
#include <stdlib.h>

int main() {
  {
    printf("*** test ***\n");
    int array[] = {[1] = 1, [3] = 3, [5] = 5};
    int sz = sizeof(array) / sizeof(int);
    printf("size(array) = %d\n", sz);
    for (int i = 0; i < sz; i++) {
      printf("array[%d]: %d\n", i, array[i]);
    }
  }
  {
    printf("*** test ***\n");
    int array[] = {[1 ... 3] = 1, [5 ... 9] = 3};

    printf("size(array) = %ld\n", sizeof(array) / sizeof(int));

    for (int i = 0; i < 10; i++) {
      printf("array[%d]: %d\n", i, array[i]);
    }
  }
  {
    printf("*** test ***\n");
    struct Data {
      int i1;
      int i2;
      double d;
    };

    struct Data d1 = {.i1 = 1, .d = 2};
    printf("[i1 = %d; i2 = %d; d = %f]\n", d1.i1, d1.i2, d1.d);
    struct Data d2 = {.i1 = 3, .i2 = 3};
    printf("[i1 = %d; i2 = %d; d = %f]\n", d2.i1, d2.i2, d2.d);
  }
  {
    printf("*** test ***\n");
    struct Data {
      int i1;
      int i2;
      double d;
    };

    struct Data darr[] = {
      [0].i1 = 1, [0].i2 = 2,
      [1 ... 3].d = 2.222,
      [1 ... 3].i1 = 22
    };

    int sz = sizeof(darr) / sizeof(struct Data);
    for (int i = 0; i < sz; i++) {
      printf("[i1 = %d; i2 = %d; d = %f]\n", darr[i].i1, darr[i].i2, darr[i].d);
    }
  }

  return 0;
}