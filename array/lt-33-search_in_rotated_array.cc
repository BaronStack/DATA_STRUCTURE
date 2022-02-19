class Solution {
public:
    // Binary seach
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            // condition1: equal.
            if (nums[mid] == target) return mid;
            // condition2: mid < 右边界 表示右半部分有序
            if (nums[mid] < nums[right]) {
                // target 在有序的部分 [mid, right]
                if (nums[mid] < target && target <= nums[right])
                    left = mid + 1;
                // target 在 无序部分
                else 
                    right = mid - 1;
            // condition3: mid > 左边界，表示左半部分有序
            } else {
                // target 在有序的部分 [left, mid]
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                // target 在无序部分
                } else {
                    left = mid + 1;
                }
            }
        }
        return -1;
    }
};
