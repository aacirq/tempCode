#include <iostream>
#include <memory>
#include <string>

using namespace std;

int main() {
  shared_ptr<int> pi1 = make_shared<int>(42);
  shared_ptr<string> pstr1 = make_shared<string>(10, 'a');
  shared_ptr<int> pi2 = make_shared<int>();

  auto pi3 = make_shared<int>(42);
  auto pstr2 = make_shared<string>(10, 'b');
  auto pi4 = make_shared<int>();

  return 0;
}