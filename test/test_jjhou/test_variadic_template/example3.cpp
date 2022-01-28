#include <algorithm>
#include <initializer_list>
#include <iostream>

// maximum of a list of number
// way1: initializer_list
template <typename ForwardIterator>
inline ForwardIterator max_itr(ForwardIterator first, ForwardIterator last) {
  ForwardIterator result = first;
  while (first != last) {
    if (*first > *result) {
      result = first;
    }
    ++first;
  }
  return result;
}

template <typename T> inline T max(std::initializer_list<T> ilst) {
  return *max_itr(ilst.begin(), ilst.end());
}

// way2: variadic template
template <typename T> T maximum(T const &arg) { return arg; }

template <typename T, typename... Types>
T maximum(T const &arg1, Types const &... args) {
  return std::max(arg1, maximum(args...));
}

int main() {
  std::cout << max({57, 48, 60, 100, 20, 18}) << std::endl;

  std::cout << maximum(57, 48, 60, 100, 20, 18) << std::endl;

  return 0;
}
