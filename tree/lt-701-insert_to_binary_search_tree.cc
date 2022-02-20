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
    // method1
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (!root) return new TreeNode(val);
        if (root->val < val) {
            root->right = insertIntoBST(root->right, val);
        } else {
            root->left = insertIntoBST(root->left, val);
        }
        return root;
    }

    // method2
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        TreeNode* p = root;
        if (p == nullptr) {
            TreeNode* new_node = new TreeNode(val);
            p = new_node;
            return p;
        }

        insertEle(p, val);
        return root;
    }
    TreeNode* insertEle(TreeNode* p, int val) {

        if (p->val > val) {
            if (!p->left) {
                p->left = new TreeNode(val);
                return p;
            } else {
                return insertIntoBST(p->left, val);
            }
        } else {
            if (!p->right) {
                p->right = new TreeNode(val);
                return p;
            } else {
                return insertIntoBST(p->right, val);
            }
        }
    }
};
