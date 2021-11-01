#include <iostream>
#include <utility>

using namespace std;

class Shape {
 public:
  Shape() {}
  virtual ~Shape() {}
};

class Circle : public Shape {
 public:
  Circle() {}
  ~Circle() {}
};

void foo(const Shape &) { cout << "foo(const Shape &)" << endl; }

void foo(Shape &&) { cout << "foo(Shape &&)" << endl; }

#if 0
// 分开写的版本
void bar(const Shape &s) {
  cout << "bar(const Shape &)" << endl;
  foo(s);
}

void bar(Shape &&s) {
  cout << "bar(Shape &&)" << endl;
  foo(s);
  // s的类型为右值类型，但是s本身为左值，调用foo时调用的是foo(const Shape &)版本
}
#endif

// 利用forward统一bar(const Shape &)和bar(Shape &&)
template <typename T>
void bar(T&& s) {
  cout << "bar(T &&)" << endl;
  foo(std::forward<T>(s));
}
// 如果推导出类型T为左值引用类型，即T为type &类型，则形参变成type& &&类型，
// 这是会发生引用坍缩，变成type &类型，即左值引用

int main() {
  bar(Circle());
  return 0;
}