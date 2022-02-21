/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    // method1 : traverse
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode new_node(0, head);
        ListNode* pre_node = &new_node;

        while(pre_node->next && pre_node->next->next) {
            if (pre_node->next->val == pre_node->next->next->val) {
                int x = pre_node->next->val;
                while (pre_node->next && pre_node->next->val == x) {
                    pre_node->next = pre_node->next->next;
                }
            } else {
                pre_node = pre_node->next;
            }
        }
        return new_node.next;
    }

    // method2 : recursion.
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) return head;
        if (head->val != head->next->val) {
            head->next = deleteDuplicates(head->next);
            return head;
        } else {
            ListNode* tmp = head->next;
            while (tmp && head->val == tmp->val) {
                tmp = tmp->next;
            }
            return deleteDuplicates(tmp);
        }
    }
};
