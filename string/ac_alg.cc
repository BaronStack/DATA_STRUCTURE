#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// Trie nodeinfo
class AcNode {
 public:
  char data_;          // AcNode char
  bool isEndingChar_;  // Ending pos
  int length_;         // Length of the string
  AcNode *children_[26];
  AcNode *fail;  // fail pointer

  AcNode(char data = '/') : data_(data), isEndingChar_(false), length_(0) {
    memset(children_, 0, sizeof(AcNode *) * 26);
  };
};

// Trie tree info with a root node
class Trie {
 public:
  Trie() { root_ = new AcNode(); }
  ~Trie() { destory(root_); }

  void insert(string des);
  bool find(string des);
  void printTrie();
  void printTrieWithPrefix(string prefix);
  void destory(AcNode *p);
  void dfsTraverse(AcNode *p, string buf, vector<string> &tmp_str);
  void bfsBuildFailPointer();
  void match(string des);
  void matchLow(string des);

 private:
  AcNode *root_;
};

// Delete the AcNode, and release the space
void Trie::destory(AcNode *p) {
  if (p == nullptr) {
    return;
  }

  for (int i = 0; i < 26; i++) {
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

  for (i = 0; i < des.size(); i++) {
    // The des[i] insert position at trie tree.
    int index = des[i] - 'a';
    if (tmp->children_[index] == nullptr) {
      AcNode *newNode = new AcNode(des[i]);
      tmp->children_[index] = newNode;
    }
    tmp = tmp->children_[index];
  }

  tmp->isEndingChar_ = true;
  tmp->length_ = des.size();
}

// Traverse the trie tree recursion
void Trie::dfsTraverse(AcNode *p, string buf, vector<string> &tmp_str) {
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
      dfsTraverse(p->children_[i], buf + (p->children_[i]->data_), tmp_str);
    }
  }
}

// Print the trie tree with dictionary order
void Trie::printTrie() {
  vector<string> tmp_str;
  int i, j;

  for (i = 0; i < 26; i++) {
    string buff = "";
    if (root_->children_[i] != nullptr) {
      // Will be called recursion
      dfsTraverse(root_->children_[i], buff + root_->children_[i]->data_,
                  tmp_str);
    }
  }

  cout << "Trie string: " << tmp_str.size() << endl;
  for (j = 0; j < tmp_str.size(); j++) {
    cout << tmp_str[j] << endl;
  }
}

// Input the prefix, and search the prefix related string
void Trie::printTrieWithPrefix(string start) {
  vector<string> tmp_str;
  int i, j;
  AcNode *tmp = root_;

  // Ensure prefix is exist
  for (int i = 0; i < start.size(); i++) {
    int index = start[i] - 'a';
    if (tmp->children_[index] == nullptr) {
      cout << "No prefix with " << start << endl;
      return;
    }
    tmp = tmp->children_[index];
  }

  // Prefix is a matched string
  tmp_str.push_back(start);

  for (i = 0; i < 26; i++) {
    string buff = start;
    if (tmp->children_[i] != nullptr) {
      // Will be called recursion
      dfsTraverse(tmp->children_[i], buff + tmp->children_[i]->data_, tmp_str);
    }
  }

  cout << "Trie string: " << tmp_str.size() << endl;
  for (j = 0; j < tmp_str.size(); j++) {
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

  for (i = 0; i < des.size(); i++) {
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

// Build the fail pointer in trie node.
// The process is just like the next array in kmp alg.
void Trie::bfsBuildFailPointer() {
  queue<AcNode *> Q;
  // Init the root fail pointer
  root_->fail = nullptr;
  Q.push(root_);

  while (!Q.empty()) {
    // Get the first element from queue, the element will be
    // removed later
    AcNode *tmp = Q.front();
    Q.pop();
    // Build the fail pointer relationship with ervery children_
    for (int i = 0; i < 26; i++) {
      AcNode *pc = tmp->children_[i];
      if (pc == nullptr) {
        continue;
      }

      if (tmp == root_) {
        pc->fail = nullptr;
      } else {
        // Check the tmp's children_ pc and q's children_ qc
        // if they have the same char ,then  pc -> fail = qc
        // Or, q while back to last fail pointer
        AcNode *q = tmp->fail;
        while (q != nullptr) {
          AcNode *qc = q->children_[pc->data_ - 'a'];
          if (qc != nullptr) {
            pc->fail = qc;
            break;
          }

          // Let the fail pointer move forward
          // Until the q->data_ == qc -> data_
          //
          // Just like the getNext in kmp, k = next[k],
          // util you find the des[k+1] == des[i+1].
          // Then you can make sure you have find the best
          // prefix in current string.
          q = q->fail;
        }

        // qc's char is not equal with pc'c char in all q's fail pointer
        // keep pc's fail pointer to root_
        if (q == nullptr) {
          pc->fail = root_;
        }
      }

      Q.push(pc);
    }
  }
}

// Match the des string with fail pointer
void Trie::match(string des) {
  AcNode *p = root_;
  int des_len = des.size();
  int i;
  vector<pair<int, int>> match_vec;

  for (i = 0; i < des_len; i++) {
    int index = des[i] - 'a';
    // case2: try to match the des[i]，if failed，traverse
    while (p->children_[index] == nullptr && p != root_) {
      p = p->fail;
    }

    p = p->children_[index];
    if (p == nullptr) {
      p = root_;
    }

    AcNode *tmp = p;
    // Keep the tmp is not nullptr
    while (tmp != nullptr && tmp != root_) {
      if (tmp->isEndingChar_ == true) {
        int pos = i - tmp->length_ + 1;
        cout << "pos: " << pos << " len :" << tmp->length_ << endl;
        match_vec.push_back(make_pair(pos, tmp->length_));
      }
      tmp = tmp->fail;
    }
  }

  // Below is to output the replace result in with match str
  // in trie tree.
  if (match_vec.size() == 0) {
    cout << "string : " << des << " has no match str in trie tree!" << endl;
    return;
  }

  int j = 0;
  int tmp;
  i = match_vec[j].first;
  // case1: check the des[i]'s fail pointer ,if the fail pointer
  // is endingchar, and we will know that we have find a matching
  // string, record it.
  while (i < des_len && j < match_vec.size()) {
    tmp = match_vec[j].second;
    while (tmp--) {
      des[i++] = '*';
    }
    j++;
  }
  cout << "string : " << des << " match !" << endl;
}

// Match trie str with traditional method.
void Trie::matchLow(string des) {
  vector<pair<int, int>> match_vec;
  AcNode *tmp = root_;
  int des_len = des.size();
  int i = 0;

  while (i < des_len) {
    int index = des[i] - 'a';
    AcNode *p = tmp->children_[index];

    while (p != nullptr) {
      i++;
      p = p->children_[des[i] - 'a'];
    }

    if (p->isEndingChar_ == true) {
      int pos = i - p->length_ + 1;
      match_vec.push_back(make_pair(pos, p->length_));
      cout << "pos: " << pos << " len :" << tmp->length_ << endl;
    } else {
      i++;
    }
  }
}

int main() {
  string s[5] = {"adafs", "dfgh", "amkil", "doikl", "aop"};

  Trie *trie = new Trie();

  for (int i = 0; i < 5; i++) {
    trie->insert(s[i]);
  }
  // Construct the fail pointer in trie tree
  trie->bfsBuildFailPointer();

  trie->printTrie();

  string prefix_str;
  cout << "Input a match string :" << endl;
  cin >> prefix_str;
  trie->match(prefix_str);
  return 0;
}
