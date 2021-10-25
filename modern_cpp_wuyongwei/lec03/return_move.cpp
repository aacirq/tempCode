/**
 * 验证函数返回时，C++11倾向于将局部变量移动出去（不使用std::move()）
 */

#include <iostream>

using namespace std;

class Obj {
 public:
  Obj() { cout << "Obj()" << endl; }

  Obj(const Obj &other) { cout << "Obj(const Obj &)" << endl; }

  Obj(Obj &&other) { cout << "Obj(Obj &&other)" << endl; }
};

Obj simple() {
  Obj obj;
  return obj;
}

Obj simple_with_move() {
  Obj obj;
  return std::move(obj);
}

Obj complicated(int n) {
  Obj obj1;
  Obj obj2;
  if (n % 2 == 0) {
    return obj1;
  } else {
    return obj2;
  }
}

int main() {
  cout << "*** 1 ***" << endl;
  auto obj1 = simple();
  // 简单返回对象：一般有NRVO(named return value optimization)
  // *** 1 ***
  // Obj()

  cout << "*** 2 ***" << endl;
  auto obj2 = simple_with_move();
  // move会禁止NRVO
  // *** 2 ***
  // Obj()
  // Obj(Obj &&other)

  cout << "*** 3 ***" << endl;
  auto obj3 = complicated(42);
  // 有分支，一般无NRVO
  // *** 3 ***
  // Obj()
  // Obj()
  // Obj(Obj &&other)

  return 0;
}