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
    // 非递归
    vector<int> inorderTraversal(TreeNode* root) {
        if (root == nullptr) return res;
        stack<TreeNode*> st;
        TreeNode* curr = root;
        while (!st.empty() || curr) {
            if (curr) { // 所有左节点入栈
                st.push(curr);
                curr = curr->left;
            } else {
                TreeNode* tmp = st.top();
                st.pop();
                res.push_back(tmp->val);
                curr = tmp->right;
            }
        }
        return res;
    }

    // 递归
    vector<int> inorderTraversalRecur(TreeNode* root) {
        if (root == nullptr) return res;
        inorderTraversal(root->left);
        res.push_back(root->val);
        inorderTraversal(root->right);
        return res;
    }
};
