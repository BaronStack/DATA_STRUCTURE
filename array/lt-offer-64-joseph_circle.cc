class Solution {
 public:
  // 方法一：找到每次要删除的元素的下标即可
  int lastRemaining(int n, int m) {
    vector<int> res;
    for (int i = 0; i < n; i++) res.push_back(i);

    int idx = 0;
    while (n > 1) {
      idx = (idx + m - 1) % n;
      res.erase(res.begin() + idx);
      n--;
    }
    return res[0];
  }

  // 方法二：递归
  int f(int n, int m) {
    if (n == 1) {
      return 0;
    }
    int x = f(n - 1, m);
    return (m + x) % n;
  }

  // 方法三：迭代/动态规划
  // dp[i] = (dp[i-1] + m) % i
  int lastRemaining(int n, int m) {
    int x = 0;
    for (int i = 2; i <= n; i++) {
      x = (x + m) % i;
    }
    return x;
  }
};
