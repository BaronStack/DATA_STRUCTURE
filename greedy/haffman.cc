#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <string>
 
using namespace std;
 
class Node {
  public:
    char c;
    int frequency;
    Node *left;
    Node *right;
    int visit;
 
    Node(char _c, int f, Node *l = nullptr, Node *r = nullptr,
         int vit = 0)
      :c(_c), frequency(f), left(l), right(r),visit(vit) { }
 
    bool operator<(const Node &node) const { 
      return frequency > node.frequency;
    }
};

struct cmp {
  bool operator() (Node a, Node b) {
    return a.frequency > b.frequency;
  }
};
 
void initNode(priority_queue<Node> &q,map<char, int> buf) {
  for (map<char, int>::iterator it = buf.begin();
                                it != buf.end();
                                it ++) {

    Node node(it->first, it->second);
    q.push(node);
  }
}
 
void showNode(priority_queue<Node> q) {
  while (!q.empty()) {
    Node node = q.top(); q.pop();
    cout << node.c << ", " << node.frequency << endl;
  }
}
 
void huffmanTree(priority_queue<Node> &q) {
  while (q.size() != 1) {
    Node *left = new Node(q.top()); 
    q.pop();
    Node *right = new Node(q.top()); 
    q.pop();
 
    Node node('R', left->frequency + 
                    right->frequency, left, right);
    q.push(node);
  }
}
 
void huffmanCode(Node *root, string &prefix,
                 map<char, string> &result) {
  string m_prefix = prefix;
 
  if (root->left == nullptr)
    return;
 
  prefix += "0";
  if (root->left->left == nullptr) {
    result[root->left->c] = prefix;
    //cout << root->left->c << ": " << prefix << endl;
  } else {
    huffmanCode(root->left, prefix, result);
  }
 
  prefix = m_prefix;
 
  prefix += "1";
  if (root->right->right == nullptr) {
    result[root->right->c] = prefix;
    //cout << root->right->c << ": " << prefix << endl;
  } else {
    huffmanCode(root->right, prefix, result);
  }
}

bool huffmanDecode(Node *root, string des,
                   string &result) {
  if (des == "" || root == nullptr) {
    return false;
  }

  Node *tmp = root; 
  int i;
  for (i = 0; i < des.size();) {
    if (des[i] == '0' && tmp -> left != nullptr) {
      tmp = tmp -> left;
      i++;
    }
    if (des[i] == '1' && tmp -> right != nullptr) {
      tmp = tmp -> right;
      i++;
    }

    if (des[i] != '0' && des[i] != '1') {
      break;
    }

    if(tmp -> left == nullptr && 
       tmp -> right == nullptr) {
      if (tmp -> visit == 0) {
        result += tmp -> c;
        tmp->visit = 1;
        tmp = root;
      } else {
        break;
      }
    }
  }
  
  if(i == des.size() - 1 && tmp == nullptr) {
    return true;
  } else {
    return false;
  }
}

void testResult(map<char, string> result) {
  map<char, string>::const_iterator it = result.begin();
  while (it != result.end()) {
    cout << it->first << ": " << it->second << endl;
    ++it;
  }
}

void initInput(string des, map<char, int> &buf) {
  if (des.size() == 0) {
    return;
  }

  for (int i = 0;i < des.size(); i ++) {
    buf[des[i]] ++;
  }
}

int main() {
  priority_queue<Node> q;
  string des;
  
  cout << "Input string: " << endl;
  cin >> des;
 
  map <char, int> buf;
  initInput(des, buf);
  initNode(q, buf);

  // print huffman tree node
  showNode(q);
  // construct the huffman tree
  huffmanTree(q);
 
  Node root = q.top();
  string prefix = "";
  map<char, string> result;
  // finish the huffman encode 
  huffmanCode(&root, prefix, result);
 
  // print encode's result for every letter
  testResult(result);

  string decode_des;
  string res;

  cout << "Input decode string : " << endl;
  cin >> decode_des;
  
  if(huffmanDecode(&root, decode_des, res)) {
    cout << "decode res: " << res << endl;
  } else {
    cout << "decode res is false ! " <<  res << endl;
  }

  return 0;
}
