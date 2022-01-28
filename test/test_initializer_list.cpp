#include <iostream>
#include <initializer_list>
#include <vector>

using namespace std;

class Seq {
  public:
  Seq(initializer_list<int> l) {
    auto b = l.begin();
    auto e = l.end();
  }
};

int main() {
  // cout << "Test initilized_list" << endl;
  // vector<int> vec_i = {1, 2, 3, 4, 5};
  // Seq t = {1, 2, 3, 4, 5};
  initializer_list<int> l{1, 2, 3, 4, 5};

  int a = 1, b = 2;

  return 0;
}