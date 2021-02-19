#include <iostream>
#include <stack>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

typedef struct AvlNode{
  int data;
  struct AvlNode *left = nullptr;
  struct AvlNode *right = nullptr;
}AvlTree, *TreeNode;

// Avl Tree : Binary search tree
class AvlAPI{
public:
  AvlAPI();
  ~AvlAPI();

  void create_avltree(TreeNode *node, AvlTree *insert);
  bool search(AvlTree *root, int target);
  void insert_avltree(TreeNode *node);
  void preOrder(AvlTree *node, int layer);
  void destory(AvlTree *node);

  TreeNode root_;
};

// Construct a AvlTree with a TreeNode input.
// Two rules:
// 1. Left node is less than the parent's value
// 2. Right node is bigger than the parent's value
void AvlAPI::create_avltree(TreeNode *node, AvlTree *insert) {
  if ((*node) -> data > insert -> data) {
    if ((*node) -> left) {
      create_avltree(&(*node) ->left,insert);
    } else {
      (*node) -> left = insert;
    }
  } else {
    if ((*node)  -> right) {
      create_avltree(&(*node) ->right, insert);
    } else {
      (*node)  -> right = insert;
    }
  }
}

// Search a value in avl tree.
// Compare with the parent's value ,if it is bigger than
// parent's value, it's better to compare the parent's right.
// Else ,compare target with the parent's left.
bool AvlAPI::search(AvlTree *root, int val) {
  if(val == root -> data) {
    return true;
  } 

  if(val < root -> data) {
    if (root -> left != nullptr) {
      return search(root -> left, val);
    } else {
      return false;
    }
  } else {
    if (root -> right != nullptr) {
      return search(root -> right, val);
    } else {
      return false;
    }
  }
}

// Insert a tree node into avl tree
void AvlAPI::insert_avltree(TreeNode *root) {
  int node_num;
  cout << "Input node nums: " << endl;
  cin >> node_num;

  for (int i = 0;i < node_num; i++) {
    int tmp;
    cin >> tmp;
    AvlTree *node = (AvlTree *)malloc(sizeof(AvlTree));
    node -> data = tmp;
    create_avltree(&(*root), node);
  }
}

// Preorder traverse the whole tree.
void AvlAPI::preOrder(AvlTree *root, int layer) {
  if (root == nullptr) {
    return;
  }
  for (int i = 0;i < layer; ++i) {
    cout << "----";
  }
  cout << root -> data << endl;
  preOrder(root -> left,layer + 1);
  preOrder(root -> right, layer + 1);
}

AvlAPI::~AvlAPI() {
  if (root_ != nullptr) {
    destory(root_);
  }
}

// Destory function to release the space
void AvlAPI::destory(AvlTree *root) {
  if (root == nullptr) {
    return;
  }

  if (root -> left != nullptr) {
    destory(root->left);
    free(root->left);
    root -> left = nullptr;
  } else if(root -> right != nullptr) {
    destory(root -> right);
    free(root -> right);
    root -> right = nullptr;
  }
}

// Init the avl tree
// For every user, you need let him know the 
// foundation element. So that other nodes could 
// compare with it.
AvlAPI::AvlAPI() {
  root_ = (AvlTree *)malloc(sizeof(AvlTree));
  root_ -> data = 8;
  root_ -> left = nullptr;
  root_ -> right = nullptr;
}

int main() {
  AvlAPI avltree;

  avltree.insert_avltree(&avltree.root_);

  cout << "Preorder :" << endl;
  avltree.preOrder(avltree.root_, 0);

  int target;
  cout << "Input the target num :" << endl;
  cin >> target;
  
  string s = (avltree.search(avltree.root_, target)==1)?"success":"failed";
  cout << "\nsearch " << target << " in tree "<< s << endl;

  return 0;
}
