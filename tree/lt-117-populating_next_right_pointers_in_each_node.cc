/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
 public:
  // 方法一：非递归
  Node* connect(Node* root) {
    if (!root) return root;
    queue<Node*> qu;
    Node* p = root;
    qu.push(p);
    // 层序遍历即可
    while (!qu.empty()) {
      int size = qu.size();
      Node* prev = nullptr;
      for (int i = 0; i < size; i++) {
        Node* curr = qu.front();
        qu.pop();
        if (!prev) {
          prev = curr;
        } else {
          prev->next = curr;
          prev = curr;
        }

        if (i == size - 1) curr->next = nullptr;

        if (curr->left) qu.push(curr->left);
        if (curr->right) qu.push(curr->right);
      }
    }
    return p;
  }
};
