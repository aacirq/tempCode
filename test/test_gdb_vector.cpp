#include <iostream>
#include <vector>

void fun(const std::vector<int> &vec) {
  for (auto i : vec) {
    std::cout << i << std::endl;
  }
}

int main(int argc, char *argv[]) {
  std::cout << "argv: ";
  for (int i = 0; i < argc; ++i) {
    std::cout << argv[i] << " ";
  }
  std::cout << std::endl;

  int ti = 0;
  std::vector<int> vec{1, 2, 3, 4, 5, 6};
  int arr_i[6];

  ti = 2;
  ti = 3;
  fun(vec);

  for (int i = 0; i < vec.size(); ++i) {
    arr_i[i] = vec[i];
  }

  int a = 22;
  for (int i = 0; i < 5; ++i) {
    std::cout << "a = " << a << std::endl;
  }

  return 0;
}