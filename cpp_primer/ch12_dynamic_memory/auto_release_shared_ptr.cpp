#include <iostream>
#include <memory>

using namespace std;

class Type {
public:
  Type() { std::cout << "Type::Type()" << std::endl; }
  ~Type() { std::cout << "Type::~Type()" << std::endl; }
};

void fun() { auto p = make_shared<Type>(); }

shared_ptr<Type> fun2() {
  auto p = make_shared<Type>();
  return p;
}

int main() {
  cout << "*** test 1 ***" << endl;

  fun();

  cout << "*** test 2 ***" << endl;

  auto p = fun2();

  cout << "*** test 3 ***" << endl;

  return 0;
}