#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int cmp(pair<int, int> a, pair<int, int> b) {
  if (a.second < b.second) {
    return 1;
  } else if (a.second == b.second && a.first < b.first) {
    return 1;
  } else {
    return 0;
  }
}

// algorithm:
// 1. Sort the array with right node increase
// 2. Maintain a num e, if rest of the interval's left node
// bigger than e, then the interval will be choosen
//
// example:
// Befor sort: [6,8], [2,4], [3,5], [1,5], [5,9], [8,10]
// After sort: [2,4], [1,5], [3,5], [6,8], [5,9], [8,10]
//
// result : [2,4], [6,8], [8,10]
void intervalCoverage(vector<pair<int, int>> intervals,
                      vector<pair<int, int>> &result) {
  if (intervals.size() == 0) {
    return;
  }

  int i, e, count;

  sort(intervals.begin(), intervals.end(), cmp);

  e = -1;
  count = 0;
  for (i = 0; i < intervals.size(); i++) {
    if (intervals[i].first >= e) {
      count++;
      e = intervals[i].second;
      result.push_back(make_pair(intervals[i].first, intervals[i].second));
    }
  }
}

int main() {
  vector<pair<int, int>> intervals;
  vector<pair<int, int>> result;

  int num_intervals;
  cout << "Input num intervals :" << endl;
  cin >> num_intervals;

  cout << "Input intervals: " << endl;
  for (int i = 0; i < num_intervals; i++) {
    int first, second;
    cin >> first >> second;

    intervals.push_back(make_pair(first, second));
  }

  intervalCoverage(intervals, result);

  cout << "Num of no intersect is: " << result.size() << endl;
  for (int i = 0; i < result.size(); i++) {
    cout << "[" << result[i].first << " , " << result[i].second << "]" << endl;
  }

  return 0;
}
