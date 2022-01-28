#include <iostream>

using namespace std;

int main() {
  int i = 1;
  int **a = new int *[5];
  a[0] = &i;

  cout << *a[0] << endl;
  return 0;
}