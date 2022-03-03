class Solution {
 public:
  // 方法一：双指针
  vector<vector<int>> res;
  vector<vector<int>> findContinuousSequence(int target) {
    int i, j;
    int size = target / 2 + 1;
    vector<int> tmp;
    int sum = 0;
    for (int i = 1, j = 1; i <= size && j <= size;) {
      sum += j;
      if (sum == target) {
        tmp.push_back(j);
        res.push_back(tmp);
        tmp.clear();
        sum = 0;
        i++;
        j = i;
      } else if (sum < target) {
        tmp.push_back(j);
        j++;
      } else {
        tmp.clear();
        sum = 0;
        i++;
        j = i;
      }
    }
    return res;
  }

  // 双指针优化版本
  vector<vector<int>> findContinuousSequence(int target) {
    int i, j;
    int size = target / 2 + 1;
    int sum = 0;
    for (int i = 1, j = 1; i <= size && j <= size;) {
      sum += j;
      if (sum == target) {
        vector<int> tmp;
        for (int k = i; k <= j; k++) {
          tmp.push_back(k);
        }
        res.push_back(tmp);
        sum = 0;
        i++;
        j = i;
      } else if (sum < target) {
        j++;
      } else {
        sum = 0;
        i++;
        j = i;
      }
    }
    return res;
  }

  // 方法二 ： 数学
  vector<vector<int>> findContinuousSequence(int target) {
    vector<vector<int>> vec;
    vector<int> res;
    int sum = 0,
        limit = (target - 1) / 2;  // (target - 1) / 2 等效于 target / 2 下取整
    for (int x = 1; x <= limit; ++x) {
      long long delta = 1 - 4 * (x - 1ll * x * x - 2 * target);
      if (delta < 0) {
        continue;
      }
      int delta_sqrt = (int)sqrt(delta + 0.5);
      if (1ll * delta_sqrt * delta_sqrt == delta && (delta_sqrt - 1) % 2 == 0) {
        int y = (-1 + delta_sqrt) /
                2;  // 另一个解(-1-delta_sqrt)/2必然小于0，不用考虑
        if (x < y) {
          res.clear();
          for (int i = x; i <= y; ++i) {
            res.emplace_back(i);
          }
          vec.emplace_back(res);
        }
      }
    }
    return vec;
  }
};
