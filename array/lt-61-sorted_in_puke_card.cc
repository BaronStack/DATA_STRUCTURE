class Solution {
public:
    // 方法1:
    // 统计 0 的个数 和 数字之间的差值，
    // 用0的个数填充 差值，满足则就是true.
    bool isStraight(vector<int>& nums) {
        int zero_nums = 0;
        int total_delta = 0;
        std::sort(nums.begin(), nums.end());
        for (int i = 0;i < 4; i++) {
            if (nums[i] == 0) zero_nums ++;
            else {
                if (nums[i+1] == nums[i]) return false;
                if (nums[i] + 1 != nums[i]) {
                    total_delta += nums[i+1] - nums[i] - 1;
                }
            }
        }
        if (zero_nums >= total_delta) return true;
        return false;
    }

    // 方法2:
    // 统计0的个数，最后的结果如果 max - min < 5 ，则表示满足，否则不满足
    // 排序后的一个数组[0,0,1,3,6], max 是 6， min 是1，如果他们之间超过5，
    // 则表示无论多少个0，都无法满足排序规则。
    bool isStraight(vector<int>& nums) {
         int zero_nums = 0;
         int total_delta = 0;
         std::sort(nums.begin(), nums.end());
         for (int i = 0;i < 4; i++) {
             if (nums[i] == 0) zero_nums ++;
             else if (nums[i+1] == nums[i]) return false;
         }
         return (nums[4] - nums[zero_nums]) < 5;
    }
};
