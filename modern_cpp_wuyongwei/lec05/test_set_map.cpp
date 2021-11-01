#include <iostream>
#include <set>
#include <map>
#include <functional>
#include <algorithm>
#include <string>

using namespace std;

template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
  cout << "(" << p.first << ", " << p.second << ")";
}

template <typename Container>
void display(const Container &con) {
  for (auto e : con) {
    cout << e << " ";
  }
  cout << endl;
}

int main() {
  // set
  set<int> s{1, 1, 1, 2, 3, 4};
  display(s);

  // multiset
  multiset<int, greater<int>> ms{1, 1, 1, 2, 3, 4};
  display(ms);

  // map
  map<string, int> mp{{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}};
  display(mp);

  mp.insert({"four", 4});
  display(mp);

  cout << (mp.find("four") == mp.end() ? "true" : "false") << endl;
  cout << (mp.find("five") == mp.end() ? "true" : "false") << endl;

  mp["five"] = 5;
  display(mp);

  // multimap
  multimap<string, int> mmp{{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}};
  display(mmp);

  mmp.insert({"four", -4});
  display(mmp);

  // find
  cout << mp.find("four")->second << endl;

  // lower_bound & upper_bound
  cout << mp.lower_bound("four")->second << endl;
  cout << (--mp.upper_bound("four"))->second << endl;
  cout << mmp.lower_bound("four")->second << endl;
  cout << (--mmp.upper_bound("four"))->second << endl;

  // equal_range
  multimap<string, int>::iterator lower, upper;
  std::tie(lower, upper) = mmp.equal_range("four");
  cout << (lower != upper ? "true" : "false") << endl;
  cout << (lower->second) << endl;
  cout << ((--upper)->second) << endl;

  return 0;
}