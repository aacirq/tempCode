#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  list<int> lst{1, 7, 2, 8, 3};
  vector<int> vec{1, 7, 2, 8, 3};

  sort(vec.begin(), vec.end());

  cout << "vec: ";
  for (auto i : vec) {
    cout << i << " ";
  }
  cout << endl;

  // sort(lst.begin(), lst.end()); // ERROR
  lst.sort();

  // list<T>的merge, remove, remove_if, reverse, sort, unique是单独定义的

  cout << "lst: ";
  for (auto i : lst) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}