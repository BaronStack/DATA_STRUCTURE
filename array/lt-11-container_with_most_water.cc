// 思路：
// 双指针 l, r 分别从容器的左边和右边向中间移动。
// 容器的底部长度是固定的，不论是左指针向右移动还是右
// 指针向左移动，对面积的影响只有1。
// 如果想让整个面积最大，移动的时候需要保留较高的元素，
// 较低的元素的部分可以进行移动。
class Solution {
public:
    int maxArea(vector<int>& height) {
        int size = height.size();
        int l = 0, r = size - 1;
        int area = 0;
        while (l < r) {
            area = max(area, (r - l) * min(
                       height[l], height[r]));
            if (height[l] > height[r]) r --;
            else l++;
        }
        return area;
    }
};
