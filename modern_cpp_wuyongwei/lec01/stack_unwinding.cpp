/**
 * 验证在发生异常时，仍然会执行析构函数
 */
#include <iostream>

class Obj {
 public:
  Obj() { puts("Obj()"); }

  ~Obj() { puts("~Obj()"); }
};

void foo(int n) {
  Obj obj;
  if (n == 42) {
    throw "life, the universe and everything";
  }
}

int main() {
  try {
    foo(41);
    foo(42);
  } catch (const char *s) {
    puts(s);
  }
  return 0;
}