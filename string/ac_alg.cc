#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

// Trie nodeinfo
class AcNode {

public:
  char data_;
  AcNode *children_[26];
  bool isEndingChar_;

  AcNode(char data='/') 
  :data_(data),isEndingChar_(false){
    memset(children_, 0, sizeof(AcNode *)* 26);
  };
};

// Trie tree info with a root node
class Trie {
public: 
  Trie() {
    root_ = new AcNode();
  }
  ~Trie() {
    destory(root_);
  }

  void insert(string des);
  bool find(string des);
  void printTrie();
  void printTrieWithPrefix(string prefix);
  void destory(AcNode *p);
  void dfs_traverse(AcNode *p, string buf, 
      vector<string> &tmp_str);

private:
  AcNode *root_;
};

// Delete the AcNode, and release the space
void Trie::destory(AcNode *p) {
  if (p == nullptr) {
    return;
  }

  for (int i = 0;i < 26; i++) {
    destory(p->children_[i]);
  }

  delete p;
  p = nullptr;
}

void Trie::insert(string des) {
  if (des.size() <= 0) {
    return;
  }

  AcNode *tmp = root_;
  int i;

  for (i = 0;i < des.size(); i++) {
    // The des[i] insert position at trie tree.
    int index = des[i] - 'a';
    if (tmp->children_[index] == nullptr) {
      AcNode *newNode = new AcNode(des[i]);
      tmp->children_[index] = newNode; 
    }
    tmp = tmp->children_[index];
  }

  tmp->isEndingChar_ = true;
}

// Traverse the trie tree recursion
void Trie::dfs_traverse(AcNode *p, string buf, 
                       vector<string> &tmp_str) {
  if (p == nullptr) {
    return;
  }

  // if match, just and the result to vector
  if (p->isEndingChar_ == true) {
    tmp_str.push_back(buf);
  }

  for (int i = 0; i < 26; i++) {
    if (p->children_[i] != nullptr) {
      // Just add the prefix every time
      dfs_traverse(p->children_[i], buf+(p->children_[i]->data_), tmp_str);
    }
  }
}

// Print the trie tree with dictionary order
void Trie::printTrie() {
  vector<string> tmp_str;
  int i, j;

  for (i = 0;i < 26; i++) {
    string buff = "";
    if (root_->children_[i] != nullptr) {
      // Will be called recursion
      dfs_traverse(root_->children_[i], 
          buff + root_->children_[i]->data_, tmp_str);
    }
  }

  cout << "Trie string: " << tmp_str.size() << endl;
  for (j = 0;j < tmp_str.size(); j++) {
    cout << tmp_str[j] << endl;
  }
}

// Input the prefix, and search the prefix related string
void Trie::printTrieWithPrefix(string start) {
  vector<string> tmp_str;
  int i, j;
  AcNode *tmp = root_;

  // Ensure prefix is exist
  for (int i = 0;i < start.size(); i++) {
    int index = start[i] - 'a';
    if (tmp->children_[index] == nullptr) {
      cout << "No prefix with " << start << endl;
      return;
    } 
    tmp = tmp->children_[index];
  }

  // Prefix is a matched string
  tmp_str.push_back(start);

  for (i = 0;i < 26; i++) {
    string buff = start;
    if (tmp->children_[i] != nullptr) {
      // Will be called recursion
      dfs_traverse(tmp->children_[i], 
          buff + tmp->children_[i]->data_, tmp_str);
    }
  }

  cout << "Trie string: " << tmp_str.size() << endl;
  for (j = 0;j < tmp_str.size(); j++) {
    cout << tmp_str[j] << endl;
  }
}

// Judge if a string is match with Trie tree
bool Trie::find(string des) {
  if (des.size() == 0) {
    return false;
  }

  AcNode *tmp = root_;
  int i;
  
  for (i = 0;i < des.size(); i++) {
    // The index of the current char's position
    int index = des[i] - 'a';
    if (tmp->children_[index] == nullptr) {
      return false;
    }

    // Move the tmp to the next line
    tmp = tmp->children_[index];
  }

  // End position to ensure wether the input str is match.
  if (tmp->isEndingChar_ == false) {
    return false;
  }

  return true;
}
