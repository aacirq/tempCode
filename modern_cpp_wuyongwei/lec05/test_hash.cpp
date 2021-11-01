#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template <typename Container>
void display(const Container &con) {
  for_each(con.begin(), con.end(), [](int i){ cout << i << " "; });
  cout << endl;
}

int main() {
  vector<int> vec{13, 6, 4, 11, 29};

  display(vec);

  sort(vec.begin(), vec.end());
  display(vec);

  sort(vec.begin(), vec.end(), greater<int>());
  display(vec);

  cout << hex;

  auto hp = hash<int *>();
  cout << "hash(nullptr)    = " << hp(nullptr) << endl;
  cout << "hash(vec.data()) = " << hp(vec.data()) << endl;
  cout << "vec.data()       = " << static_cast<void *>(vec.data()) << endl;

  auto hs = hash<string>();
  cout << "hash(\"hello\") = " << hs(string("hello")) << endl;
  cout << "hash(\"hellp\") = " << hs(string("hellp")) << endl;

  return 0;
}