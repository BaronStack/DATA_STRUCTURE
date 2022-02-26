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
  bool res = false;
  bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if (!root && !subRoot) {
      return true;
    }
    if (!root && subRoot) {
      return false;
    }
    return checkTree(root, subRoot) || isSubtree(root->left, subRoot) ||
           isSubtree(root->right, subRoot);
  }

  bool checkTree(TreeNode* node, TreeNode* sub) {
    if (!node && !sub) return true;
    if (node && sub) {
      if (node->val != sub->val) return false;
      return checkTree(node->left, sub->left) &&
             checkTree(node->right, sub->right);
    }
    return false;
  }
};
