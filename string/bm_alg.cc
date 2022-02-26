#include <iostream>
#include <map>
#include <string>
#include <vector>

#define MAP_SIZE 256

using namespace std;

// storage the des's position
//
// @params:
// des: destination string
// mp: update the relationship between char in
// des with it's index in des
//
// examples:
// s t r _ e x a m p l e
// 0 1 2 3 4 5 6 7 8 9 10
//
// mp['s'] = 0
// ...
// mp['e'] = 10
// ....
void generateBC(string des, map<char, int> &mp) {
  int i;

  for (i = 0; i < des.size(); i++) {
    // and the map relationship between des's
    // element with it's position
    mp[des[i]] = i;
  }
}

// generate suffix and prefix arr
//
// @params:
// des: destination str
// suffix: the first position of the suffix str in des
// prefix: if the suffix exist in prefix of des, update
// prefix arr vector<bool> to true
//
// examples:
// des: b a b c a b
// pos: 0 1 2 3 4 5
// suffix: b, ab, cab, bcab, abcab
// suffix[1] = 0
// suffix[2] = 1
// suffix[3] = -1
// suffix[4] = -1
// suffix[5] = -1
//
// prefix[1] = true
// prefix[2] = true
// prefix[3] = false
// ...
void generateGS(string des, vector<int> &suffix, vector<bool> &prefix) {
  int i;
  int des_len = des.size();

  for (i = 0; i < des_len; i++) {
    suffix.push_back(-1);
    prefix.push_back(false);
  }

  // traverse the prefix str , update the suffix vector
  // and prefix vector
  for (i = 0; i < des_len - 1; i++) {
    int j = i;  // prefix start index
    int k = 0;

    while (j >= 0 && des[j] == des[des_len - 1 - k]) {
      --j;
      ++k;
      suffix[k] = j + 1;
    }

    if (j == -1) {
      prefix[k] = true;
    }
  }
}

// move the des str to a position
//
// @params:
// j: bad char's index
// des: destination string
// suffix: suffix in des's start index
// prefix: wether the suffix math with prefix
//
// case:
// src: a b c a c a b c b c b a c a b c
// des: c b a c a b c
int movePosition(int j, string des, vector<int> suffix, vector<bool> prefix) {
  // case1: move to the longest len of sufix
  int k = des.size() - 1 - j;
  if (suffix[k] != -1) {
    return j - suffix[k] + 1;
  }

  // case2: move to other suffix position
  //
  // longest suffix's range [j+1, len(des)-1]
  // other suffix's range [j+2, len(des)-1]
  for (int r = j + 2; r <= des.size() - 1; r++) {
    if (prefix[des.size() - r] == true) {
      return r;
    }
  }

  // case3: move the len of des
  return des.size();
}

// boyer-moore algorithm
//
// two rules:
// 1. bad char
// 2. good suffix
int bm_alg(string src, string des) {
  map<char, int> last_pos;
  vector<int> suffix;
  vector<bool> prefix;

  generateBC(des, last_pos);
  generateGS(des, suffix, prefix);

  int i = 0;
  int src_len = src.size();
  int des_len = des.size();

  while (i <= (src_len - des_len)) {
    int j;

    // find the bad char
    for (j = des_len - 1; j >= 0; j--) {
      if (src[i + j] != des[j]) {
        break;
      }
    }

    if (j < 0) {
      return i;
    }

    // bad char's move position
    int x = j - last_pos[src[i + j]];
    int y = 0;

    // good suffix's move position
    if (j < des_len - 1) {
      y = movePosition(j, des, suffix, prefix);
    }

    // move the max of position between badchar and
    // good suffix
    i = i + std::max(x, y);
  }

  return -1;
}

int main() {
  string src;
  string des;

  cout << "input src ";
  cin >> src;

  cout << "input des ";
  cin >> des;

  if (bm_alg(src, des) != -1) {
    printf("%s is the substr of %s with index : %d\n", des.c_str(), src.c_str(),
           bm_alg(src, des));
  } else {
    printf("not match \n");
  }

  return 0;
}
