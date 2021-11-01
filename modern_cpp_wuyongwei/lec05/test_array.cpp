#include <iostream>
#include <array>
#include <map>
#include <array>

using namespace std;

template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
  cout << "(" << p.first << ", " << p.second << ")";
}

ostream &operator <<(ostream &os, const array<char, 8> arr) {
  os << arr.data();
}

template <typename Container>
void display(const Container &con) {
  for (auto e : con) {
    cout << e << " ";
  }
  cout << endl;
}

int main() {
  map<array<char, 8>, int> mp;
  array<char, 8> mykey{"hello"};
  mp[mykey] = 5;
  display(mp);

  return 0;
}