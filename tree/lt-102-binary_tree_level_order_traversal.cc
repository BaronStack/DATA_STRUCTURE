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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (root == nullptr) return res;
        queue<TreeNode*> qu;
        qu.push(root);

        while(!qu.empty()) {
            int size = qu.size();
            vector<int> tmp;
            for (; size != 0; size --) {
                TreeNode* node = qu.front();
                qu.pop();
                tmp.push_back(node->val);
                
                if (node->left) qu.push(node->left);
                if (node->right) qu.push(node->right);
            }
            res.push_back(tmp);
        }
        return res;
    }
};
