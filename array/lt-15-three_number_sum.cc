class Solution {
 public:
  vector<vector<int>> res;
  vector<vector<int>> threeSum(vector<int>& nums) {
    if (nums.size() < 2) return res;
    std::sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size() - 1; i++) {
      if (nums[0] > 0) return res;
      if (i > 0 && nums[i] == nums[i - 1]) {  // 去重
        continue;
      }
      vector<int> tmp;
      int target = 0 - nums[i];
      // 双指针查找指定的数组
      for (int l = i + 1, r = nums.size() - 1; l < r;) {
        if (nums[l] + nums[r] == target) {
          tmp.push_back(nums[i]);
          tmp.push_back(nums[l]);
          tmp.push_back(nums[r]);
          res.push_back(tmp);
          tmp.clear();
          l++, r--;
          // 去重
          while (l < r && nums[l] == nums[l - 1]) l++;
          while (l < r && nums[r] == nums[r + 1]) r--;
        } else if (nums[l] + nums[r] > target) {
          r--;
        } else {
          l++;
        }
      }
    }
    return res;
  }
};
