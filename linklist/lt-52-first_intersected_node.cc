/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
 public:
  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    int l1 = 0, l2 = 0;
    ListNode *p1 = headA, *p2 = headB;
    while (p1) {
      l1++;
      p1 = p1->next;
    }

    while (p2) {
      l2++;
      p2 = p2->next;
    }
    p1 = headA, p2 = headB;
    if (l1 > l2) {
      int tmp = l1 - l2;
      while (tmp != 0) {
        p1 = p1->next;
        tmp--;
      }
    } else {
      int tmp = l2 - l1;
      while (tmp != 0) {
        p2 = p2->next;
        tmp--;
      }
    }

    while (p1 && p2) {
      if (p1 == p2) return p1;
      p1 = p1->next;
      p2 = p2->next;
    }
    return nullptr;
  }
};
