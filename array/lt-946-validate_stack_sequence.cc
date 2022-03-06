class Solution {
 public:
  // 同样的方法，模拟，两种实现方式
  bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
    int i = 0, j = 0;
    std::stack<int> moni;
    int N = pushed.size();
    for (auto ele : pushed) {
      moni.push(ele);
      while (j < N && !moni.empty() && moni.top() == popped[j]) {
        moni.pop();
        j++;
      }
    }

    return j == N;
  }

  bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
    int i = 0, j = 0;
    std::stack<int> moni;
    while (i < pushed.size() || j < popped.size()) {
      if ((moni.empty() || moni.top() != popped[j]) && i < pushed.size()) {
        moni.push(pushed[i]);
        i++;
      } else if (moni.top() == popped[j]) {
        moni.pop();
        j++;
      } else {
        break;
      }
    }

    if (moni.empty() && j == popped.size()) return true;
    return false;
  }
};
