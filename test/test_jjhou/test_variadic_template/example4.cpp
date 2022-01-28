#include <bitset>
#include <iostream>
#include <tuple>

// different operation between first and last element
// variadic template: example 4
template <int IDX, int MAX, typename... Types> struct PRINT_TUPLE {
  static void print(std::ostream &os, std::tuple<Types...> const &t) {
    os << std::get<IDX>(t) << (IDX + 1 == MAX ? "" : ",");
    PRINT_TUPLE<IDX + 1, MAX, Types...>::print(os, t);
  }
};

template <int MAX, typename... Types> struct PRINT_TUPLE<MAX, MAX, Types...> {
  static void print(std::ostream &os, std::tuple<Types...> const &t) {}
};

template <typename... Types>
std::ostream &operator<<(std::ostream &os, std::tuple<Types...> const &t) {
  os << "[";
  PRINT_TUPLE<0, sizeof...(Types), Types...>::print(os, t);
  os << "]";
  return os;
}

int main() {
  auto t = std::make_tuple(7.5, std::string("hello"), std::bitset<16>(377),
                               42);

  // std::cout << std::get<2>(t) << std::endl;
  std::cout << t << std::endl;

  return 0;
}
