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
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        if (abs(dfs(root->left) - dfs(root->right)) <= 1) {
            return isBalanced(root->left) && isBalanced(root->right);
        }
        return false;
    }

    int dfs(TreeNode* node) {
        if(!node) return 0;
        return max(dfs(node->left), dfs(node->right)) + 1;
    }
};
