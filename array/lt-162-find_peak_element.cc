class Solution {
public:
    // method1: search as array's order
    int findPeakElement(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        if (nums.size() == 2) return nums[1] > nums[0] ? 1: 0;
        int i;
        for (i = 0;i < nums.size() - 1; i++) {
            if (nums[i] > nums[i+1]) return i;
        }
        if (i == nums.size() - 1 && nums[i] > nums[i-1]) return i;
        return 0;
    }
    
    // method2: binary search with two rules:
    // 1. nums[mid] > nums[mid+1], peak should in left bound.
    // 2. nums[mid] < nums[mid+1], peak should in right bound.
    //
    // input : [1,2,3,4,5,3,1]
    // output : 4.  is the index of 5
    int findPeakElement(vector<int>& nums) {
        int i, j;
        for (i = 0, j = nums.size() - 1; i < j;) {
            int mid = (i + j) / 2;
            if (nums[mid] > nums[mid+1]) {
                j = mid;
            } else {
                i  = mid + 1;
            }
        }
        return i;
    }
};
