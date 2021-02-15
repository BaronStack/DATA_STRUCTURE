#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>

using namespace std;

struct HaffNode {
  char data;
  string code;
  int frequency;

  HaffNode *left;
  HaffNode *right;

  HaffNode(char c, int freq) {
    data = c;
    frequency = freq;

    left = nullptr;
    right = nullptr;
  }
};

struct cmp {
  bool operator() (pair<char,int> a, pair<char, int> b){
    return a.second < b.second;
  }
};

HaffNode* getHaffmanTree(string s) {
  if (s.size() == 0) {
    return nullptr;
  }

  priority_queue<pair<char ,int >, 
    vector<pair<char, int>>, cmp> Q;
  map <char,int> tmp;
  int i;

  // Caculate every letter's frequency
  for (i = 0;i < s.size(); i ++) {
    tmp[s[i]] ++;
  }

  // Construct the queue from smaller data to bigger data
  for (map<char,int>::iterator it = tmp.begin(); 
                                it != tmp.end();it ++) {
    cout << "first : " << it->first 
         << " second : " << it->second
         << endl;
    Q.push(make_pair(it->first, it->second));
  }

  cout << "priority_queue size : " << Q.size() << endl;
  HaffNode *left, *right;
  HaffNode *r;
  while(!Q.empty()) {
    left = (HaffNode *)malloc(sizeof(HaffNode));
    left -> data = Q.top().first;
    left -> frequency = Q.top().second;
    Q.pop();
    if (!Q.empty()) {
      right = new HaffNode(Q.top().first, Q.top().second);
      right -> data = Q.top().first;
      right -> frequency = Q.top().second;
      right -> code += '0'; 
      Q.pop();
    } else {
      break;
    }

    HaffNode *root = (HaffNode *) malloc(sizeof(HaffNode));
    root -> data = left->data - '0' + right->data - '0';
    root -> left = left;
    root -> right = right;
    root -> frequency = left -> frequency + right -> frequency;
    Q.push(make_pair(root -> data,root -> frequency));

    r = root;
  }
  
  return r;
}

void getHaffCode(HaffNode *root) {
  if (root == nullptr) {
    return;
  }

  if (root -> left == nullptr && 
      root -> right == nullptr) {
    cout << "letter: " << root -> data
         << " code: " << root -> code
         << endl;
  }

  getHaffCode(root->left);
  getHaffCode(root->right);
}

int main() {
  string des;
  cout << "Input string : " << endl;
  cin >> des;

  cout << "Haffman code is : " << endl;
  getHaffCode(getHaffmanTree(des));
  return 0;
}
