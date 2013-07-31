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
    ListNode *deleteDuplicates(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode *next, *current;
        
        current = head;
        while (current) {
            next = current->next;
            if (next && current->val == next->val) {
                current->next = next->next;
                free(next);
            } else {
                current = next;
            }
        }
        
        return head;
    }
};
