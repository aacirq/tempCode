#include <iostream>
#include <iterator>
#include <list>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
  int numIslands(vector<vector<char>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    int root1, root2;
    s = vector<int>(m * n, -1);
    for (int i = 1; i < m; i++) {
      if (grid[i][0] == '1' && grid[i - 1][0] == '1') {
        root1 = find((i - 1) * n);
        root2 = find(i * n);
        unionSet(root1, root2);
      }
    }
    for (int i = 1; i < n; i++) {
      if (grid[0][i] == '1' && grid[0][i - 1] == '1') {
        root1 = find(i - 1);
        root2 = find(i);
        unionSet(root1, root2);
      }
    }
    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        if (grid[i][j] == '1') {
          if (grid[i - 1][j] == '1') {
            root1 = find((i - 1) * n + j);
            root2 = find(i * n + j);
            unionSet(root1, root2);
          }
          if (grid[i][j - 1] == '1') {
            root1 = find(i * n + j - 1);
            root2 = find(i * n + j);
            if (root1 != root2)
              unionSet(root1, root2);
          }
        }
      }
    }
    int res = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == '1' && s[i * n + j] < 0) {
          ++res;
        }
      }
    }
    return res;
  }

private:
  vector<int> s;

  int find(int x) {
    if (s[x] < 0) {
      return x;
    } else {
      return s[x] = find(s[x]);
    }
  }

  void unionSet(int root1, int root2) { s[root2] = root1; }
};

int main() {
  {
    Solution sol;
    vector<vector<char>> grid{{'1', '1', '1', '1', '0'},
                              {'1', '1', '0', '1', '0'},
                              {'1', '1', '0', '0', '0'},
                              {'0', '0', '0', '0', '0'}};
    cout << sol.numIslands(grid) << endl;
  }
  return 0;
}