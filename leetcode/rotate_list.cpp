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
    ListNode *rotateRight(ListNode *head, int k) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        if (head == NULL) return head;
        
        ListNode *tmp, *last;
        tmp = head;
        int len;
        
        len = 0;
        while (tmp) {
            last = tmp;
            tmp = tmp->next;
            len ++;
        }
        
        
        k = (len - k % len)%len;
        
        if (len == 1 || k == 0) return head;

        
        len = 0;
        tmp = head;
        while (len < k - 1) tmp = tmp->next, len++;
        ListNode *newhead = tmp->next;
        last->next = head;
        tmp->next = NULL;
        return newhead;
        
        
        
    }
};
