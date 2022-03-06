// 方法一：优先级队列
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
  if (nums.empty() || k == 0) return vector<int>();
  int n = nums.size();
  priority_queue<pair<int, int>> q;
  for (int i = 0; i < k; ++i) {
    q.emplace(nums[i], i);
  }
  vector<int> ans = {q.top().first};
  for (int i = k; i < n; ++i) {
    q.emplace(nums[i], i);
    while (
        q.top().second <=
        i - k) {  // 窗口移动，添加了一个元素之后发现最大元素不在窗口内，则pop
      q.pop();
    }
    ans.push_back(q.top().first);
  }
  return ans;
}

// 方法二：单调队列
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
  if (nums.empty() || k == 0) return vector<int>();
  int n = nums.size();
  deque<int> q;
  for (int i = 0; i < k; ++i) {
    while (!q.empty() && nums[i] >= nums[q.back()]) {
      q.pop_back();
    }
    q.push_back(i);
  }

  vector<int> ans = {nums[q.front()]};
  for (int i = k; i < n; ++i) {
    while (!q.empty() && nums[i] >= nums[q.back()]) {
      q.pop_back();
    }
    q.push_back(i);
    while (q.front() <= i - k) {
      q.pop_front();
    }
    ans.push_back(nums[q.front()]);
  }
  return ans;
}
