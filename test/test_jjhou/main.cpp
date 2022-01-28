#include <complex>
#include <iostream>
#include <string>

int main() {
  std::string s1{"Hello"};
  std::string s2{"world"};

  []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
  }();

  s1 + s2 = s2;
  std::cout << s1 << std::endl;
  std::cout << s2 << std::endl;

  std::string() = "World";

  return 0;
}