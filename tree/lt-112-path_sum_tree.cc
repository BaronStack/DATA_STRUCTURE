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
  // Method1
  bool hasPathSum(TreeNode* root, int targetSum) {
    if (!root) return false;
    queue<TreeNode*> st;
    queue<int> st_data;
    st.push(root);
    st_data.push(root->val);
    while (!st.empty()) {
      TreeNode* node = st.front();
      st.pop();
      int tmp = st_data.front();
      st_data.pop();
      if (!node->left && !node->right) {
        if (tmp == targetSum) return true;
        continue;
      }
      if (node->left) {
        st.push(node->left);
        st_data.push(tmp + node->left->val);
      }
      if (node->right) {
        st.push(node->right);
        st_data.push(tmp + node->right->val);
      }
    }
    return false;
  }

  // Method2
  bool checkPathSum(TreeNode* node, int sum) {
    if (!node) return false;
    sum -= node->val;
    if (!node->left && !node->right) {
      return sum == 0;
    }
    return checkPathSum(node->left, sum) || checkPathSum(node->right, sum);
  }
};
