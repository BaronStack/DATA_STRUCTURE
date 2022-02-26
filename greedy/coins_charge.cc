#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int cmp(pair<int, int> a, pair<int, int> b) { return a.first > b.first; }

void getCoinNums(vector<pair<int, int>> coins, int K,
                 vector<pair<int, int>> &result) {
  if (coins.size() == 0) {
    return;
  }

  int i, tmp;

  // sort from biger to smaller
  sort(coins.begin(), coins.end(), cmp);

  i = 0;
  tmp = 0;
  while (K && i < coins.size()) {
    tmp = K / coins[i].first;

    if (tmp != 0) {
      int real_nums;
      // defend the real coin nums overhead
      if (tmp <= coins[i].second) {
        real_nums = tmp;
      } else {
        real_nums = coins[i].second;
      }

      K -= real_nums * coins[i].first;

      result.push_back(make_pair(coins[i].first, real_nums));
    }
    i++;
  }
}

int main() {
  vector<pair<int, int>> coins = {{100, 1}, {50, 3}, {20, 1}, {10, 10},
                                  {5, 5},   {2, 2},  {1, 10}};

  vector<pair<int, int>> result;
  int K = 193;

  getCoinNums(coins, K, result);

  int res_nums = 0;
  for (int i = 0; i < result.size(); i++) {
    cout << "coin: " << result[i].first << " use " << result[i].second << endl;
    res_nums += result[i].second;
  }
  cout << "Total coins is : " << res_nums << endl;

  return 0;
}
