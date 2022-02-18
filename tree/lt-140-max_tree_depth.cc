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
    // 100%
    int maxDepth(TreeNode* root) {
        return root == 0 ? 0 : max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }

    // Method2
    int maxDepth(TreeNode* root) {
        return depthRecurr(root, 0);
    }
    int dephtRecurr(TreeNode* node, int level) {
        if (node == nullptr) return level;
        return max(dephtRecurr(node->left, level + 1), dephtRecurr(node->right, level+1));
    }

    // Method3 
    int depth = 0;
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        queue<TreeNode*> qu;
        qu.push(root);
        while(!qu.empty()) {
            int size = qu.size();
            for (;size != 0; size --) {
                TreeNode* node = qu.front();
                qu.pop();
                if (node->left) qu.push(node->left);
                if (node->right) qu.push(node->right);
            }
            depth ++;
        }
        return depth;
    }
};
