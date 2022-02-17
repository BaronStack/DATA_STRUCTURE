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
    vector<int> postorderTraversal(TreeNode* root) {
        if (root == nullptr) return res;
        stack<TreeNode*> st;
        TreeNode* curr = root, *r = nullptr;
        while (!st.empty() || curr) {
            if (curr) {
                st.push(curr);
                curr = curr->left;
            } else {
                curr = st.top();
                if (curr->right == nullptr || curr->right == r) { // r保存已经访问过的右节点
                    res.push_back(curr->val);
                    r = curr;
                    st.pop();
                    curr = nullptr;
                } else {
                    curr = curr->right;
                }
            }
        }
        return res;
    }
    // Method2 : 递归
    vector<int> postorderTraversal(TreeNode* root) {
        if (root == nullptr) return vector<int>();
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        res.push_back(root->val);
        return res;
    }
};
