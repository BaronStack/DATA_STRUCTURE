class MaxQueue {
 public:
  MaxQueue() {}

  int max_value() { return q1.empty() ? -1 : q2.front(); }

  void push_back(int value) {
    q1.push(value);
    while (!q2.empty() && q2.back() < value) {
      q2.pop_back();
    }
    q2.push_back(value);
  }

  int pop_front() {
    if (q1.empty()) return -1;
    int tmp = q1.front();
    q1.pop();
    if (tmp == q2.front()) {
      q2.pop_front();
    }
    return tmp;
  }

  queue<int> q1;
  deque<int>
      q2;  // 我们只需要在插入每一个元素 value 时，
           // 从队列尾部依次取出比当前元素 value 小的元素，
           // 直到遇到一个比当前元素大的元素 value' 即可.双端队列队头保存最大值
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue* obj = new MaxQueue();
 * int param_1 = obj->max_value();
 * obj->push_back(value);
 * int param_3 = obj->pop_front();
 */
