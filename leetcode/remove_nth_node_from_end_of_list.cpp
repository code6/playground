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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
       if (n == 0) return head;
       int sz = 0;
       ListNode *ptr = head;
       while (ptr != NULL) {
           sz++;
           ptr = ptr->next;
       }
       n = sz + 1 - n;
       if (n == 1) {
           ptr = head->next;
           free(head);
           head = ptr;
       } else {
           ptr = head;
           for (int i = 0; i < n -2 ; i++) ptr = ptr->next;   
           ListNode *tmp = ptr->next;
           ptr->next = ptr->next->next;
           free(tmp);
       }       
       return head;
    }
};
