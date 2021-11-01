#include <string>
#include <iostream>

using namespace std;

int main() {
  string name;
  cout << "What's your name? ";
  getline(cin, name);
  cout << "Nice to meek you, " << name << "!\n";

  return 0;
}