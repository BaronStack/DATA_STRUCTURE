#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// simple greedy algorithm: distribute candies
// six childs' request: 1 1 3 2 2 8
// five candies size:   4 2 5 7 9
//
// Greedy algorithm is suitable to solve the problem.
// We can let the smaller candy's size to satisfy the
// smaller resquest of child.
int distributeCandy(vector<int> candies, vector<int> childs) {
  if (candies.size() == 0 || childs.size() == 0) {
    return 0;
  }

  // sort, we can compare from small to big request
  sort(candies.begin(), candies.end());
  sort(childs.begin(), childs.end());

  int res = 0;
  int i, j;

  for (i = 0, j = 0; i < childs.size() && j < candies.size(); i++, j++) {
    if (childs[i] <= candies[j]) {
      res++;
    }
  }

  return res;
}

int main() {
  vector<int> candies = {4, 2, 5, 7, 9};
  vector<int> childs = {1, 1, 3, 2, 2, 8};

  cout << "satisfied childs' num is " << distributeCandy(candies, childs)
       << endl;
  return 0;
}
