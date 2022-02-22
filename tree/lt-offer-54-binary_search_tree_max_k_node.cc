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
    // 方法一: 
    // 中序遍历, 将所有的结点放在数组中，因为
    // 中序遍历是有序的，所以直接取 arr.size() -k 个结点即可
    int kthLargest(TreeNode* root, int k) {
        stack<TreeNode*> st;
        TreeNode* p = root;
        vector<int> tmp_vec;
        while(!st.empty() || p) {
            if (p) {
                st.push(p);
                p = p->left;
            } else {
                TreeNode* tmp = st.top();
                st.pop();
                tmp_vec.push_back(tmp->val);
                p = tmp->right;
            }
        }

        return tmp_vec[tmp_vec.size() - k];
    }

    // 方法二：
    // 中序遍历，先遍历根左子树，再遍历右子树，顺序就是倒序了.
    // 这样，直接取遍历到的第k 个结点即可。
    int kthLargest(TreeNode* root, int k) {
        stack<TreeNode*> st;
        TreeNode* p = root;
        while(!st.empty() || p) {
            if (p) {
                st.push(p);
                p = p->right;
            } else {
                TreeNode* tmp = st.top();
                st.pop();
                k--;
                if (k == 0) return tmp->val; 
                p = tmp->left;
            }
        }

        return -1;
    }
};
