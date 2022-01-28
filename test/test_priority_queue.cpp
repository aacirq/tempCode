#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::priority_queue;
using std::vector;
using std::make_heap;

void print(const vector<int> &vec) {
  cout << "[ ";
  for (auto ele : vec) {
    cout << ele << " ";
  }
  cout << "]" << endl;
}

int main() {
  vector<int> vec{1, 8, 5, 6, 3, 4, 0, 9, 7, 2};

  print(vec);

  make_heap(vec.begin(), vec.end());
  print(vec);

  return 0;
}