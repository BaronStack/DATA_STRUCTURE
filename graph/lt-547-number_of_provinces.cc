class Solution {
 public:
  void dfs(vector<vector<int>>& isConnected, vector<int>& visited,
           int provinces, int i) {
    for (int j = 0; j < provinces; j++) {
      if (isConnected[i][j] == 1 && !visited[j]) {
        visited[j] = 1;
        dfs(isConnected, visited, provinces, j);
      }
    }
  }

  // 方法1: dfs
  // 通过dfs 找到所有和当前节点 i 连通的顶点，并标记visited.
  // 对于后续扫描到没有被visited 的顶点，说明其是一个独立的顶点
  int findCircleNum(vector<vector<int>>& isConnected) {
    int provinces = isConnected.size();
    vector<int> visited(provinces);
    int circles = 0;
    for (int i = 0; i < provinces; i++) {
      if (!visited[i]) {
        dfs(isConnected, visited, provinces, i);
        circles++;
      }
    }
    return circles;
  }

  // 方法2: union-find 并查集
  class UnionFind {
   public:
    UnionFind() : cicle_nums(0) {}
    ~UnionFind() = default;
    void Add(int ele) {
      if (mp_.count(ele) == 0) {
        mp_[ele] = -1;
        cicle_nums++;
      }
    }

    int Find(int ele) {
      int root = ele;
      while (mp_[root] != -1) {
        root = mp_[root];
      }

      // path compression.
      while (ele != root) {
        int origin_root = mp_[ele];
        mp_[ele] = root;
        ele = origin_root;
      }
      return root;
    }

    void Union(int x, int y) {
      int x_root = Find(x);
      int y_root = Find(y);

      if (x_root != y_root) {
        mp_[x_root] = y_root;
        cicle_nums--;
      }
    }

    bool IsConnected(int x, int y) { return Find(x) == Find(y); }

    int GetCirculNums() { return cicle_nums; }

   private:
    int cicle_nums;
    unordered_map<int, int> mp_;
  };

  // 利用并查集进行查找
  int findCircleNum(vector<vector<int>>& isConnected) {
    int size = isConnected.size();
    UnionFind uf;

    for (int i = 0; i < size; i++) {
      uf.Add(i);
      for (int j = 0; j < i; j++) {
        // 发现两个节点是连通的，确定他们是在一个集合
        // 并尝试进行合并.
        if (isConnected[i][j]) {
          uf.Union(i, j);
        }
      }
    }
    return uf.GetCirculNums();
  }
};
