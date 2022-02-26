class Solution {
 public:
  // method :
  // 1. double pointer -- most effeciency
  // 2. hashtable
  // 3. binary search
  //
  // input : [2,7,11,15], 9
  // output : [2,7] or [7,2]
  vector<int> twoSum(vector<int>& nums, int target) {
    for (int i = 0, j = nums.size() - 1; i <= j;) {
      int sum = nums[i] + nums[j];
      if (sum == target)
        return {nums[i], nums[j]};
      else if (sum > target) {
        j--;
      } else {
        i++;
      }
    }
    return {-1, -1};
  }
};
