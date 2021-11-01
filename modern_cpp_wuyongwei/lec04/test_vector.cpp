#include <iostream>
#include <vector>

using namespace std;

class Obj1 {
 public:
  Obj1() { cout << "Obj1()" << endl; }

  Obj1(const Obj1 &other) { cout << "Obj1(const Obj1 &)" << endl; }

  Obj1(Obj1 &&other) { cout << "Obj1( &&)" << endl; }
};

class Obj2 {
 public:
  Obj2() { cout << "Obj2()" << endl; }

  Obj2(const Obj2 &other) { cout << "Obj2(const Obj2 &)" << endl; }

  Obj2(Obj2 &&other) noexcept { cout << "Obj2(Obj2 &&)" << endl; }
};

int main() {
  vector<Obj1> v1;
  v1.reserve(2);
  v1.emplace_back();
  v1.emplace_back();
  v1.emplace_back();
  /**
   * 由于Obj1的移动构造函数没有声明noexcept，
   * 当因预分配空间不足而重新分配内存的时候，vector会调用拷贝构造函数
   */

  vector<Obj2> v2;
  v2.reserve(2);
  v2.emplace_back();
  v2.emplace_back();
  v2.emplace_back();
  /**
   * 由于Obj2的移动构造函数声明了noexcept，
   * 所以当重新分配内存的时候，vector调用移动构造函数。
   * 对于拷贝代价较高的元素类型，这可以大大减少消耗。
   */

  /**
   * 应当为类定义noexcept的移动构造函数
   */

  return 0;
}
