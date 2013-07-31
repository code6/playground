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
    void addnode(ListNode* & head, ListNode* & tail, ListNode *ptr) {
        ListNode *current = new ListNode(ptr->val);
        if (head == NULL) {
            head = tail = current;
        } else {
            tail->next = current;
            tail = current;
        }
    }
    void merge_list(ListNode* & first, ListNode* &ftail, 
                    ListNode* & second, ListNode* &stail) {
                        if (ftail == NULL) {
                            first = second;
                        } else {
                            ftail->next = second;
                        }
                    }
    ListNode *partition(ListNode *head, int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode *first, *pfirst;
        ListNode *second, *psecond;
        first = second = NULL;
        pfirst = psecond = NULL;
        for (ListNode *ptr = head; ptr != NULL; ptr=ptr->next) {
            if (ptr->val < x) {
                addnode(first, pfirst, ptr);
            } else {
                addnode(second, psecond, ptr);
            }
        }
        merge_list(first, pfirst, second, psecond);
        return first;
    }
};
