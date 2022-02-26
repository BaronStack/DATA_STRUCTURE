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
  // Method1
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode pre_node(0);
    ListNode* new_node = &pre_node;
    while (l1 && l2) {
      if (l1->val <= l2->val) {
        new_node->next = l1;
        l1 = l1->next;
      } else {
        new_node->next = l2;
        l2 = l2->next;
      }
      new_node = new_node->next;
    }
    if (l1) {
      new_node->next = l1;
    }
    if (l2) {
      new_node->next = l2;
    }

    return pre_node.next;
  }

  // Method2 recurrsion
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    if (l1->val <= l2->val) {
      l1->next = mergeTwoLists(l1->next, l2);
      return l1;
    } else {
      l2->next = mergeTwoLists(l1, l2->next);
      return l2;
    }
  }

  // Method3 similar to method1
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode pre_node(0);
    ListNode* new_node = &pre_node;
    while (l1 || l2) {
      if (!l1) {
        new_node->next = l2;
        break;
      }
      if (!l2) {
        new_node->next = l1;
        break;
      }

      if (l1->val <= l2->val) {
        new_node->next = l1;
        l1 = l1->next;
      } else {
        new_node->next = l2;
        l2 = l2->next;
      }
      new_node = new_node->next;
    }
    return pre_node.next;
  }
};
