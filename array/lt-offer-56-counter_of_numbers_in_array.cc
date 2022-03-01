class Solution {
  // 方法1 ：高阶玩法
  vector<int> singleNumbers(vector<int>& nums) {
    //因为相同的数字异或为0，任何数字与0异或结果是其本身。
    //所以遍历异或整个数组最后得到的结果就是两个只出现一次的数字异或的结果：即 z
    //= x ^ y
    int z = 0;
    for (auto i : nums) z ^= i;
    //我们根据异或的性质可以知道：z中至少有一位是1，否则x与y就是相等的。
    //我们通过一个辅助变量m来保存z中哪一位为1.（可能有多个位都为1，我们找到最低位的1即可）。
    //举个例子：z = 10 ^ 2 = 1010 ^ 0010 = 1000,第四位为1.
    //我们将m初始化为1，如果（z & m）的结果等于0说明z的最低为是0
    //我们每次将m左移一位然后跟z做与操作，直到结果不为0.
    //此时m应该等于1000，同z一样，第四位为1.
    int m = 1;
    while ((z & m) == 0) m <<= 1;
    //我们遍历数组，将每个数跟m进行与操作，结果为0的作为一组，结果不为0的作为一组
    //例如对于数组：[1,2,10,4,1,4,3,3]，我们把每个数字跟1000做与操作，可以分为下面两组：
    // nums1存放结果为0的: [1, 2, 4, 1, 4, 3, 3]
    // nums2存放结果不为0的: [10]
    // (碰巧nums2中只有一个10，如果原数组中的数字再大一些就不会这样了)
    //此时我们发现问题已经退化为数组中有一个数字只出现了一次
    //分别对nums1和nums2遍历异或就能得到我们预期的x和y
    int x = 0, y = 0;
    while (auto i : nums) {
      //这里我们是通过if...else将nums分为了两组，一边遍历一遍异或。
      //跟我们创建俩数组nums1和nums2原理是一样的。
      if ((i & m) == 0)
        x ^= i;
      else
        y ^= i;
    }
    return vector<int>{x, y};
  }

  // 方法2 ： 消耗较多空间的hash表方式
  vector<int> singleNumbers(vector<int>& nums) {
    unordered_map<int, int> mp;
    for (auto ele : nums) {
      if (!mp.count(ele)) {
        mp[ele]++;
        continue;
      }

      if (mp.count(ele)) {
        mp.erase(ele);
        continue;
      }
    }
    vector<int> res;
    for (auto p : mp) {
      res.push_back(p.first);
    }
    return res;
  }
}
