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
    ListNode *swapPairs(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode *phead = head, *pprev = NULL;
        while (phead !=NULL && phead->next != NULL) {
            ListNode *pnext = phead->next;
            if (pprev != NULL) {
                pprev->next = pnext;
            } else {
                head = pnext;
            }           
            phead->next = pnext->next;
            pnext->next = phead;
            pprev = phead;
            phead = phead->next;            
        }
        return head;
    }
};
