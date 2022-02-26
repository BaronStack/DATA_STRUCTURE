class Solution {
 public:
  // 1. 先排序
  // 2. 排序过程的比较，只需要关注x + y < y + x 即可
  //    x + y < y +x ，则 x < y; 否则  x + y > y + x ，x > y
  string minNumber(vector<int>& nums) {
    if (nums.size() == 0) return "";
    vector<string> str_vec;
    string res;
    str_vec.reserve(nums.size());
    for (auto& num : nums) {
      str_vec.push_back(to_string(num));
    }
    std::sort(str_vec.begin(), str_vec.end(), cmp);
    for (auto str : str_vec) {
      res += str;
    }
    return res;
  }
  static bool cmp(const string& a, const string& b) { return a + b < b + a; }
};
