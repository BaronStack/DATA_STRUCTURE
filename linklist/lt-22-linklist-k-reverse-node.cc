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
  ListNode* getKthFromEnd(ListNode* head, int k) {
    ListNode* fast = head;
    while (fast) {
      fast = fast->next;
      if (k == 0) {
        head = head->next;
      } else {
        k--;
      }
    }
    return head;
  }
};
