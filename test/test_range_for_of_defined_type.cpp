#include <iostream>
#include <iterator>

using std::cout;
using std::endl;

class Number : public std::iterator<int, int> {
public:
  explicit Number(int n) : a(n) {}

  int operator*() { return a; }

  bool operator!=(Number const &rhs) { return (a != rhs.a); }

  Number operator++() {
    Number tmp(this->a);
    a++;
    return tmp;
  }

private:
  int a;
};

int num[] = {1, 4, 3, 5, 2, 6, 4, 8, 9, 0};

class Type {
public:
  Type() = default;

  Number begin() const { return Number(0); }

  Number end() const { return Number(10); }
};

int main() {
  Type t;

  for (auto x : t) {
    cout << x << endl;
  }

  return 0;
}
