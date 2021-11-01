/**
 * 验证临时对象的生命期：
 *   一个临时对象会在包含这个临时对象的完整表达式完成后，按生成顺序的逆序销毁。
 */

#include <iostream>

class Shape {
 public:
  Shape() {}
  virtual ~Shape() {}
};

class Circle : public Shape {
 public:
  Circle() { printf("Circle()\n"); }
  ~Circle() { printf("~Circle()\n"); }
};

class Triangle : public Shape {
 public:
  Triangle() { printf("Triangle()\n"); }
  ~Triangle() { printf("~Triangle()\n"); }
};

class Rectangle : public Shape {
 public:
  Rectangle() { printf("Rectangle()\n"); }
  ~Rectangle() { printf("~Rectangle()\n"); }
};

class Result {
 public:
  Result() { printf("Result()\n"); }
  ~Result() { printf("~Result()\n"); }
};

Result process_shape(const Shape &shape1, const Shape &shape2) {
  printf("process_shape()\n");
  return Result();
}

int main() {
  printf("main()\n");
  process_shape(Circle(), Triangle());
  printf("something else\n");
}