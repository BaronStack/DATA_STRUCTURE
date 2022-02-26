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
  bool isSymmetric(TreeNode* root) {
    if (root == nullptr) return false;
    return checkTree(root->left, root->right);
  }

  bool checkTree(TreeNode* l, TreeNode* r) {
    if (!l && r) return false;
    if (l && !r) return false;
    if (!l && !r) return true;

    if (l->val == r->val) {
      return checkTree(l->left, r->right) && checkTree(l->right, r->left);
    } else {
      return false;
    }
  }

  // Method2
  bool isSymmetric(TreeNode* root) {
    TreeNode *q = root, *p = root;
    queue<TreeNode*> qu;
    qu.push(q);
    qu.push(p);
    while (!qu.empty()) {
      TreeNode* q1 = qu.front();
      qu.pop();
      TreeNode* p1 = qu.front();
      qu.pop();

      if (!q1 && !p1) continue;
      if ((!q1 || !p1) || (q1->val != p1->val)) return false;

      qu.push(q1->left);
      qu.push(p1->right);

      qu.push(q1->right);
      qu.push(p1->left);
    }
    return true;
  }
};
