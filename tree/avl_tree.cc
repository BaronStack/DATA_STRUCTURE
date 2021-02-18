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

//   AvlTree() {
//     left = nullptr;
//     right = nullptr;
//   }
}AvlTree, *TreeNode;

// void create_avltree(TreeNode *root,
//                     AvlTree *node) {
//   if (node -> data >= (*root) -> data) {
//     if((*root) -> left != nullptr) {
//       create_avltree(&(*root) -> left, node);
//     } else {
//       (*root) -> left = node;
//     }
//   } else {
//     if ((*root) -> right != nullptr) {
//       create_avltree(&(*root) -> right, node);
//     } else {
//       (*root) -> right = node;
//     }
//   }
// }

void create_avltree(TreeNode *node, AvlTree *insert) {
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

bool search(AvlTree *root, int val) {
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

void insert_avltree(TreeNode *root) {
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

void preOrder(AvlTree *root, int layer) {
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

int main() {
  TreeNode root;
  root = (AvlTree *)malloc(sizeof(AvlTree));
  root -> data = 8;
  root -> left = nullptr;
  root -> right = nullptr;

  insert_avltree(&root);

  cout << "Preorder :" << endl;
  preOrder(root, 0);

  int target;
  cout << "Input the target num :" << endl;
  cin >> target;
  
	string s = (search(root, target)==1)?"success":"failed";
  cout << "\nsearch " << target << " in tree "<< s << endl;

  return 0;
}
