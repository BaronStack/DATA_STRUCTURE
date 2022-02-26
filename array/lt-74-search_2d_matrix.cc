class Solution {
 public:
  int r = 0, l = 0;
  // 1. We check the first element of the row, if it bigger than target,
  // then below the row is unnecessary to search.
  // 2. For every satisfied row, we just binary search the whole row.
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    r = matrix.size();
    l = matrix[0].size();
    for (int i = 0; i < r; i++) {
      if (matrix[i][0] > target) {
        return false;
      }
      if (binarySearch(matrix, i, target)) return true;
    }
    return false;
  }

  bool binarySearch(vector<vector<int>>& matrix, int row, int target) {
    int left = 0, right = matrix[0].size() - 1;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (matrix[row][mid] == target) return true;
      if (matrix[row][mid] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return false;
  }
};
