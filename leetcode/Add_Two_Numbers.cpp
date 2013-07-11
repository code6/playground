#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

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
    
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode * head = NULL;
        ListNode * pCurrent = NULL;
        int carriage = 0;
        int val;
        while (l1 != NULL && l2 != NULL) {
            val = l1->val + l2->val + carriage;
            l1 = l1->next;
            l2 = l2->next;
            carriage = val / 10;
            val = val % 10;
            if (pCurrent == NULL) {
                head = pCurrent = new ListNode(val);
            } else {
                pCurrent->next = new ListNode(val);
                pCurrent = pCurrent->next;
            }
        }
        
        while (l1 != NULL) {
           val = l1->val + carriage;
           carriage = val / 10;
           val = val % 10;
           l1 = l1->next;
            if (pCurrent == NULL) {
                head = pCurrent = new ListNode(val);
            } else {
                pCurrent->next = new ListNode(val);
                pCurrent = pCurrent->next;
            }
        }
        
         while (l2 != NULL) {
           val = l2->val + carriage;
           carriage = val / 10;
           val = val % 10;
           l2 = l2->next;
            if (pCurrent == NULL) {
                head = pCurrent = new ListNode(val);
            } else {
                pCurrent->next = new ListNode(val);
                pCurrent = pCurrent->next;
            }
        }
        
        if (carriage > 0) {
            pCurrent->next = new ListNode(carriage);
        }
        
        return head;
        
    }
};

int main(int argc, char *argv[]) {
	
}