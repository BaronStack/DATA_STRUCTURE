#include <iostream>
#include <vector>
#include <string>

using namespace std;

void getNext(string des, vector<int> &next) {
  next[0] = -1;
  int k = -1;
  int i;

  // i begin with 1, next[0] always is -1
  for (i = 1; i< des.size(); i++) {
    // Find the longest match prefix by judge 
    // two char dex[i] and des[k+1].
    // Just like case1 and case2: next[i-1]=k-1
    // if des[i] == des[k-1], then next[i] = next[i-1] + 1 = k;
    while(k != -1 && des[i] != des[k+1]) {
      //let 'k' storage 'next[next[...]]'
      k = next[k];
    }

    // find the match char, let k ++
    if (des[i] == des[k+1]) {
      k++;
    }

    next[i] = k;
  }
}

int kmp_alg(string src, string des) {
  if (src.size() == 0 || des.size() <= 0) {
    return -1;
  }

  int src_len = src.size();
  int des_len = des.size();
  vector<int> next;
  int i, j;
  
  
  next.resize(des_len);
  // Get the next vector
  getNext(des,next);

  j = 0;
  for (i = 0;i < src_len; i++) {
    // 1. Find the bad char
    // 2. Next[j-1] is the longest match prefix's tail index
    // move the j to the destinations.
    // 
    // Example:
    //                i
    //      0 1 2 3 4 5 6 7 8 9
    // src: a b a b a e a b a c
    // des: a b a b a c d 
    //      0 1 2 3 4 5 6
    //                j
    //
    // when find bad char: i = 5, j = 5;
    // good prefix is : ababa
    // longest match prefix : aba
    // longest match prefix tail in des: 2
    // next[j-1] : next[5-1] = 2
    // j: 2 + 1 = 3
    //
    // after slide ,the src and des is bellow:
    //                i
    //      0 1 2 3 4 5 6 7 8 9
    // src: a b a b a e a b a c
    // des:     a b a b a c d 
    //          0 1 2 3 4 5 6
    //                j
    //
    while(j > 0 && src[i] != des[j]) {
      j = next[j-1] + 1; 
    }
    
    // The good prefix, just add the j
    if (src[i] == des[j]) {
      j++;
    }

    // Match the des and return the index in srs
    if (j == des_len) {
      return (i - des_len + 1);
    }
  }
  return -1;
}

int main() {
  string s1,s2;
  cin >> s1;
  cin >> s2;

  if (kmp_alg(s1,s2) == -1) {
    cout << s1 << " with " << s2 << " not match !" << endl;
  } else {
    cout << s1 << " with " << s2 << " match !" << endl;
  }
  return 0;
}
