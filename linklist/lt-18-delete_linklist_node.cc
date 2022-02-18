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
    // Method1 recursion.
    ListNode* deleteNode(ListNode* head, int val) {
        if(head == nullptr) return head;
        if (head->val == val) return head->next;
        head->next = deleteNode(head->next, val);
        return head;
    }

    // Method2 double pointer
    ListNode* deleteNode(ListNode* head, int val) {
        if(head == nullptr) return head;
        if (head->val == val) {
            head = head->next;
            return head;
        }
        ListNode* prev = head;
        ListNode* curr = head->next;
        while (curr) {
            if (curr->val == val) {
                prev->next = curr->next;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
        return head;
    }
};
