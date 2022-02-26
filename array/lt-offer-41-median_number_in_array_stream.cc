// 主要是利用优先级队列实现的最大堆和最小堆来实现
// 最大堆存储 较小的元素，最小堆存储 较大的元素.
// 在维护这两个堆的过程中核心为
// 1. 最大堆的堆顶元素需要小于堆小堆的堆顶元素
// 2. 两个堆元素个数相差不能超过1
class MedianFinder {
 public:
  /** initialize your data structure here. */
  MedianFinder() {}
  priority_queue<int, vector<int>, greater<int>> small_heap;  // 最小堆
  priority_queue<int, vector<int>, less<int>> big_heap;       // 最大堆

  void addNum(int num) {
    if (big_heap.empty()) {
      big_heap.push(num);
      return;
    }

    // 情况1: 两个堆元素个数相等，则将较大的元素放在
    // 最小堆中,否则放在较小堆中.
    if (big_heap.size() == small_heap.size()) {
      if (num > big_heap.top()) {
        small_heap.push(num);
      } else {
        big_heap.push(num);
      }
    } else if (big_heap.size() > small_heap.size()) {
      // 情况2: 最大堆中的元素较多
      if (num <= big_heap.top()) {
        small_heap.push(big_heap.top());
        big_heap.pop();
        big_heap.push(num);
      } else {
        small_heap.push(num);
      }
    } else {
      // 情况3: 最小堆中的元素较多
      if (num >= small_heap.top()) {
        big_heap.push(small_heap.top());
        small_heap.pop();
        small_heap.push(num);
      } else {
        big_heap.push(num);
      }
    }
  }

  double findMedian() {
    if (small_heap.size() == big_heap.size()) {
      return ((double)small_heap.top() + (double)big_heap.top()) / 2.0;
    } else if (small_heap.size() > big_heap.size()) {
      return (double)small_heap.top();
    } else {
      return (double)big_heap.top();
    }
  }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
