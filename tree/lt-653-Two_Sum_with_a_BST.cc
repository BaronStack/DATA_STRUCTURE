/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
 public:
  // 方法一：先序遍历，对于每一个节点都进行一次dfs search
  // 查找的过程可以利用 bst-tree 的特性进行查找：
  // 大于根结点的节点都在右子树，小于根节点的节点都在左子树
  bool findTarget(TreeNode* root, int k) {
    if (!root) return false;

    TreeNode* tmp = root;
    stack<TreeNode*> st;
    while (!st.empty() || tmp) {
      if (tmp) {
        st.push(tmp);
        tmp = tmp->left;
      } else {
        TreeNode* q = st.top();
        st.pop();
        if (dfsSearchTree(root, q, k - q->val)) return true;
        tmp = q->right;
      }
    }
    return false;
  }

  // 需要保证查找的节点不是当前节点
  bool dfsSearchTree(TreeNode* node, TreeNode* prev, int target) {
    if (!node) return false;
    if (node->val == target && node->val != prev->val) return true;
    return node->val > target ? dfsSearchTree(node->left, prev, target)
                              : dfsSearchTree(node->right, prev, target);
  }

  // 方法二：利用先序遍历，将所有的节点放在数组中，这样就是一个有序数组
  // 再对有序数组进行 双指针一前一后查找
};
