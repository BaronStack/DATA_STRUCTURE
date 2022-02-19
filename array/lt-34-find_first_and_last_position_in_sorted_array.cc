class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.size()  == 0) return {-1, -1};
        int left = binarySearch(nums, target, true);
        int right = binarySearch(nums, target, false) - 1;
        if (right < -1 || (right - left) < 0) {
            return {-1, -1};
        }
        return {left, right};
    }

    // Binary search to find the lower_bound and upper_bound.
    int binarySearch(vector<int>& nums, int target, bool lower) {
        int left = 0, right = nums.size() - 1, ans = nums.size();
        while(left <= right) {
            int mid = (left + right) / 2;
            // If lower is true, then find the lower bound.
            if (nums[mid] > target || (lower && nums[mid] >= target)) {
                right = mid - 1;
                ans = mid;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }
};
