/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    // Method1 
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return root;
        queue<TreeNode*> qu;
        qu.push(root);
        while(!qu.empty()) {
            TreeNode* tmp = qu.front();
            qu.pop();
            // 交换当前节点的子节点
            TreeNode* r = tmp->right;
            tmp->right = tmp->left;
            tmp->left = r;

            // 将子节点添加到队列中
            if (tmp->left) qu.push(tmp->left);
            if (tmp->right) qu.push(tmp->right);
        }
        return root;
    }

    // Method2 recursion
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return root;
        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};
