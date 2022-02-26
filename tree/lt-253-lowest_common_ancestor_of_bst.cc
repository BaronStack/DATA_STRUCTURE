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
  // Method1: recurrsion.
  TreeNode* res = nullptr;
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    finder(root, p, q);
    return res;
  }

  void finder(TreeNode* root, TreeNode* p, TreeNode* q) {
    if ((root->val - p->val) * (root->val - q->val) <= 0) {
      res = root;
    } else if (root->val < p->val && root->val < q->val) {
      finder(root->right, p, q);
    } else {
      finder(root->left, p, q);
    }
  }

  // Method2 : once traverse.
  // 利用 BST 的搜索特性
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* ancess = root;
    while (ancess) {
      if (ancess->val > p->val && ancess->val > q->val) {
        ancess = ancess->left;
      } else if (ancess->val < p->val && ancess->val < q->val) {
        ancess = ancess->right;
      } else {
        break;
      }
    }
    return ancess;
  }
};
