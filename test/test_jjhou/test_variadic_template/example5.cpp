#include <iostream>
#include <string>
#include <tuple>

namespace tt {
// recursive inherit
// 原始版本
template <typename... Types> class tuple;

// 无参的特化版本
template <> class tuple<> {};

// 一般类型tuple的特化版本
template <typename Head, typename... Tail>
class tuple<Head, Tail...> : private tuple<Tail...> {
  typedef tuple<Tail...> inherited;

public:
  tuple() {}
  tuple(Head v, Tail... vtail) : m_head(v), inherited(vtail...) {}

  Head head() { return m_head; };
  inherited &tail() { return *this; };

protected:
  Head m_head;
};
} // namespace tt

int main() {
  tt::tuple<int, float, std::string> t(41, 6.3, "nico");

  std::cout << t.head() << std::endl;
  std::cout << t.tail().head() << std::endl;
  std::cout << t.tail().tail().head() << std::endl;

  return 0;
}
