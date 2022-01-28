#include <initializer_list>
#include <iostream>
#include <algorithm>

void print(std::initializer_list<int> vals) {
  for (auto i : vals) {
    std::cout << i << " ";
  }
}

class P {
 public:
  P(int a, int b) {
    std::cout << "P(int, int), a=" << a << ", b=" << b << std::endl;
  }

  P(std::initializer_list<int> intList) {
    std::cout << "P(initializer_list<int>), values=";
    for (auto i : intList) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }
};

int main() {
  {
    /**
     * 利用initilizer_list实现不定参数数量的函数
     */
    print({1, 3, 2, 4, 5, 7, 6, 8});
    std::cout << std::endl;    // 1 3 2 4 5 7 6 8
  }
  {
    /**
     * initializer_list构造函数匹配
     */
    P p1(1, 2);      // P(int, int), a=1, b=2
    P p2({2, 3});    // P(initializer_list<int>), values=2 3
    P p3{2, 3};      // P(initializer_list<int>), values=2 3
    P p4{3, 4, 5};   // P(initializer_list<int>), values=3 4 5
    P p5 = {4, 5};   // P(initializer_list<int>), values=4 5
  }
  {
    /**
     * 以initializer_list为参数的算法
     */
    std::initializer_list<int> ilst{5, 7, 4, 2, 5, 6, 3, 2, 1, 7, 3};
    std::cout << std::min(ilst) << std::endl;   // 1
    std::cout << std::max(ilst) << std::endl;   // 7
  }
  return 0;
}