class Solution {
 public:
  // 方法1: 递归
  // 当前数组的最后一个元素为跟结点
  // 二叉搜索树满足 max(left-tree) < root < min(right-tree)
  // 所以 我们只需要找到 左右子树的分界线即可利用递归
  // 分别判断左右子树
  bool verifyPostorder(vector<int>& postorder) {
    return recurr(postorder, 0, postorder.size() - 1);
  }

  bool recurr(vector<int>& postorder, int i, int j) {
    if (i >= j) return true;
    int p = i;
    while (postorder[p] < postorder[j]) p++;
    int m = p;  // 找到了 左右子树的分界线，也就是 max(left-tree) < root <
                // min(right-tree)
    while (postorder[p] > postorder[j]) p++;
    return p == j && recurr(postorder, i, m - 1) && recurr(postorder, m, j - 1);
  }

  // 方法2: 单调栈
};
