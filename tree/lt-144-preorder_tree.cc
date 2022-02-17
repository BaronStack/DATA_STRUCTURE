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
    vector<int> res;
    // Method1: 深度优先，非递归
    vector<int> preorderTraversal(TreeNode* root) {
        if (root == nullptr) return res;
        
        stack<TreeNode*> st;
        st.push(root);
        while(!st.empty()) {
            TreeNode* tmp = st.top();
            st.pop();
            res.push_back(tmp->val);
            if (tmp->right) st.push(tmp->right);
            if (tmp->left) st.push(tmp->left);
        }
        return res;
    }

    // Method2 : 递归
    vector<int> preorderTraversalRecur(TreeNode* root) {
        if (root == nullptr) return vector<int>();
        res.push_back(root->val);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
        return res;
    }

    
};
