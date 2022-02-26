class Solution {
 public:
  bool exist(vector<vector<char>>& board, string word) {
    if (board.size() == 0 || board[0].size() == 0) return false;
    for (int r = 0; r < board.size(); r++) {
      for (int c = 0; c < board[0].size(); c++) {
        if (dfs(board, r, c, word, 0)) return true;
      }
    }
    return false;
  }

  bool dfs(vector<vector<char>>& board, int row, int col, const string& word,
           int idx) {
    if (idx == word.size()) return true;
    if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size())
      return false;
    if (word[idx] != board[row][col]) return false;

    board[row][col] = '*';
    // dfs 操作
    if (dfs(board, row - 1, col, word, idx + 1) ||
        dfs(board, row + 1, col, word, idx + 1) ||
        dfs(board, row, col - 1, word, idx + 1) ||
        dfs(board, row, col + 1, word, idx + 1)) {
      return true;
    }
    // 回溯，发现不满足单词匹配的要求的时候 回溯当前字符到之前的字符
    board[row][col] = word[idx];
    return false;
  }
};
