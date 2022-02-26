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
  // method1 : normal traverse
  TreeNode* searchBST(TreeNode* root, int val) {
    if (!root) return nullptr;
    queue<TreeNode*> qu;
    qu.push(root);
    while (!qu.empty()) {
      TreeNode* node = qu.front();
      qu.pop();
      if (node->val == val) {
        return node;
      }
      if (node->left) qu.push(node->left);
      if (node->right) qu.push(node->right);
    }
    return nullptr;
  }

  // method2 : recurrsion with preorder traverse
  TreeNode* searchBST(TreeNode* root, int val) {
    if (!root || root->val == val) return root;
    return root->val > val ? searchBST(root->left, val)
                           : searchBST(root->right, val);
  }
};
