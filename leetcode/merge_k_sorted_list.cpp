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
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode *head, *current;
        
        head = current = NULL;
        
        while (true) {
            bool found = false;
            int best_val = -1;
            int best_pos = -1;
            for (int i = 0; i < lists.size(); i++) {
                if (lists[i] != NULL) {
                    if (false == found || best_val > lists[i]->val) {
                        found = true;
                        best_val = lists[i]->val;
                        best_pos = i;
                    }
                }
            }
            
            if (!found) {
                break;
            }
            
            if (head == NULL) {
                head = current = new ListNode(lists[best_pos]->val);
            } else {
                current->next = new ListNode(lists[best_pos]->val);
                current = current->next;
            }
            lists[best_pos] = lists[best_pos]->next;
        }
        
        
        return head;
    }
};
