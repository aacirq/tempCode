#include <bitset>
#include <iostream>

// Function to print variables of different types
// Variadic Templates: example 1
void printX() {}

template <typename T, typename... Types>
void printX(T const &arg1, Types const &... args) {
  std::cout << arg1 << std::endl;
  printX(args...);
}

int main() {
  printX(7.5, "hello", std::bitset<16>(377), 42);

  return 0;
}
