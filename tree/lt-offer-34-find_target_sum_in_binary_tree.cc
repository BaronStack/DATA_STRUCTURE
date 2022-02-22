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
    vector<vector<int>> res;
    vector<vector<int>> pathSum(TreeNode* root, int target) {
        vector<int> path;
        dfs(root, 0, target, path);
        return res;
    }

    void dfs(TreeNode* root, int sum, int target, vector<int>& path) {
        if (!root) return;
        sum += root->val;
        path.push_back(root->val);
        // 找到了叶子结点且和满足要求，则添加到数组中
        if (sum == target && !root->left && !root->right) {
            res.push_back(path);
        }

        dfs(root->left, sum, target, path);
        dfs(root->right, sum, target, path);

        // 回溯 ，这两步非常关键
        path.pop_back();
        sum -= root->val;
    }
};
