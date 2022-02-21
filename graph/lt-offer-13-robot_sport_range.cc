class Solution {
public:
    int total = 0;
    int movingCount(int m, int n, int k) {
        if (m == 0 && n == 0) return 0;
        vector<vector<int>> arr(m, vector<int>(n, 0));
        dfs(arr, 0, 0, k);
        for (int i = 0;i < m; i++) {
            for (int j = 0;j < n; j++) {
                if (arr[i][j] == 1) {
                    total ++;
                }
            }
        }
        return total;
    }

    void dfs(vector<vector<int>> &arr, int start, int end, int k) {
        if (start < 0 || start >= arr.size() || end < 0 || end >= arr[0].size())
            return;
        if (arr[start][end] == 1 || !check(start, end, k)) return;

        arr[start][end] = 1;
        dfs(arr, start + 1, end, k);
        dfs(arr, start, end + 1, k);
    }

    bool check(int start, int end, int k) {
        int sum  = 0;
        while (start) {
            sum += start % 10;
            start = start / 10;
        }
        while (end) {
            sum += end % 10;
            end = end / 10;
        }
        return sum <= k;
    }
};
