#include <iostream>
#include <string>
#include <complex>
#include <bitset>

namespace tt {
template <typename... Types> class tup;

template <> class tup<> {};

template <typename Head, typename... Tail> class tup<Head, Tail...> {
  typedef tup<Tail...> Composited;

public:
  tup() {}
  tup(Head head, Tail... tail) : m_head(head), m_tail(tail...) {}

  Head head() { return m_head; }
  Composited &tail() { return m_tail; }

protected:
  Head m_head;
  Composited m_tail;
};
} // namespace tt

int main() {
  tt::tup<int, float, std::string> it1(42, 6.3, "nico");
  std::cout << sizeof(it1) << std::endl;
  std::cout << it1.head() << std::endl;
  std::cout << it1.tail().head() << std::endl;
  std::cout << it1.tail().tail().head() << std::endl;

  tt::tup<std::string, std::complex<int>, std::bitset<16>, double>
    it2("Ace", std::complex<int>(3, 8), std::bitset<16>(377), 3.1415926);
  std::cout << sizeof(it2) << std::endl;
  std::cout << it2.head() << std::endl;
  std::cout << it2.tail().head() << std::endl;
  std::cout << it2.tail().tail().head() << std::endl;
  std::cout << it2.tail().tail().tail().head() << std::endl;

  return 0;
}
