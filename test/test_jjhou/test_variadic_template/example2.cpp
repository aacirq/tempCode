#include <iostream>
#include <execution>

// Implement of printf
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

int main() {
  my_printf("%d %f %p %s\n", 1, 2, 3, 4);
  return 0;
}