class Solution {
 public:
  vector<int> pancakeSort(vector<int>& arr) {
    vector<int> ret;
    // 1. 在当前数组中找到最大的元素，先反转当前位置到头部的所有元素
    // 2. 再次反转，最大的元素就到了最后的位置。
    // 3. 依次，将第二大的元素也做反转，放在末尾的次二大的位置。
    for (int n = arr.size(); n > 1; n--) {
      // 找到 n 个元素中的最大元素的 index
      int max_ele = max_element(arr.begin(), arr.begin() + n) - arr.begin();
      if (max_ele == n - 1) {
        continue;
      }

      // 反转0 .. index+1 ，即要包含最大的这个元素
      reverse(arr.begin(), arr.begin() + max_ele + 1);
      // 整体反转
      reverse(arr.begin(), arr.begin() + n);
      ret.push_back(max_ele + 1);
      ret.push_back(n);
    }
    return ret;
  }
};
