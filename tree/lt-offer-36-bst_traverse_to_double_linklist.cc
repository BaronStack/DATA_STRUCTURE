/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        inOrder(root);
        if (node_vec.size() < 1) return root;
        // 遍历数组，构造双向链表
        for (int i = 0;i < node_vec.size() - 1; i++) {
            node_vec[i]->right = node_vec[i+1];
            node_vec[i+1]->left = node_vec[i];
        }

        node_vec[0]->left = node_vec.back();
        node_vec.back()->right = node_vec[0];
        return node_vec[0];
    }
private:
    vector<Node*> node_vec;
    // 中序遍历，将所有节点放在一个数组中
    void inOrder(Node* root) {
        if (!root) return;
        stack<Node*> st;
        Node* p = root;
        while (!st.empty() || p) {
            if (p) {
                st.push(p);
                p = p->left;
            } else {
                Node* tmp = st.top();
                st.pop();
                node_vec.push_back(tmp);
                p = tmp->right;
            }
        }
    }
};
