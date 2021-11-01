#include <complex>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

namespace std {
template <typename T>
struct hash<complex<T>> {
  size_t operator()(const complex<T> &v) const noexcept {
    hash<T> h;
    return h(v.real() + v.imag());
  }
};
}  // namespace std

template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
  cout << "(" << p.first << ", " << p.second << ")";
}

template <typename Container>
void display(const Container &con) {
  for (auto e : con) {
    cout << e << " ";
  }
  cout << endl;
}

int main() {
  unordered_set<int> s{1, 1, 2, 3, 5, 8, 13, 21};
  display(s);

  unordered_map<complex<double>, double> umc{{{1.0, 1.0}, 1.4142},
                                             {{3.0, 4.0}, 5.0}};
  display(umc);
  return 0;
}