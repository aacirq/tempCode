#include <algorithm>
#include <complex>
#include <cstddef>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <bitset>

// Variadic Templates: example 1
void printX() {}

template <typename T, typename... Types>
void printX(T const &arg1, Types const &... args) {
  std::cout << arg1 << std::endl;
  printX(args...);
}

// Variadic Templates: example 2
void my_printf(char const *s) {
  while (*s) {
    if (*s == '%' && *(++s) != '%') {
      throw std::runtime_error("invalid format string: missing arguments");
    }
    std::cout << *s++;
  }
}

template <typename T, typename... Types>
void my_printf(char const *s, T const &v1, Types const &... args) {
  while (*s) {
    if (*s == '%' && *(++s) != '%') {
      std::cout << v1;
      my_printf(++s, args...);
      return;
    }
    std::cout << *s++;
  }
  throw std::logic_error("extra argument provided to printf");
}

// Variadic Templates: example 3



int main() {
  printX(7.5, "hello", std::bitset<16>(377), 42);

  return 0;
}
