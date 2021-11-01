#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

template <typename T>
ostream &operator<<(ostream &os, const pair<T, T> &p) {
  cout << "(" << p.first << ", " << p.second << ")";
}

int main() {
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      q;
  
  q.push({1, 1});
  q.push({2, 2});
  q.push({0, 3});
  q.push({9, 4});

  while (!q.empty()) {
    cout << q.top() << endl;
    q.pop();
  }

  return 0;
}