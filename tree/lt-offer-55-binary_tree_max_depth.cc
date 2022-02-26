/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
 public:
  // method1
  int maxDepth(TreeNode* root) { return dfs(root, 0); }

  int dfs(TreeNode* root, int h) {
    if (!root) return 0;
    if (!root->left && !root->right) {
      return h + 1;
    }

    int left = dfs(root->left, h + 1);
    int right = dfs(root->right, h + 1);
    return max(left, right);
  }

  // method2
  int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
  }

  // method3
  int maxDepth(TreeNode* root) {
    if (!root) return 0;
    queue<TreeNode*> qu;
    int depth = 0;
    qu.push(root);
    while (!qu.empty()) {
      int size = qu.size();
      for (; size != 0; size--) {
        TreeNode* node = qu.front();
        qu.pop();
        if (node->left) qu.push(node->left);
        if (node->right) qu.push(node->right);
      }
      depth++;
    }
    return depth;
  }
};
