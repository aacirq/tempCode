/**
 * 练习使用next_permutation算法，并查看其原理
 */
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main() {
  string str{"abcd"};
  do {
    cout << str << endl;
  } while (next_permutation(str.begin(), str.end()));
  return 0;
}