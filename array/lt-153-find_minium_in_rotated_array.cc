class Solution {
 public:
  // input : [[3,4,5,1,2]]
  // output : [1]
  int findMin(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (nums[mid] > nums[right]) {
        left = mid + 1;
      } else if (nums[mid] < nums[right]) {
        right = mid;  //不能减1，因为mid是向下取整，
                      //且当前数组是非完全递增，可能会丢失最小值
      } else {
        right--;
      }
    }
    return nums[left];
  }
};
