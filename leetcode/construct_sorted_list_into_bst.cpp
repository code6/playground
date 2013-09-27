/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode *construct(int sz, ListNode *head) {
        if (sz == 0) {
            return NULL;
        } 
        int mid = sz / 2;
        ListNode *ptr = head;
        while (mid) {
            ptr = ptr->next;
            mid --;
        }        
        TreeNode *root = new TreeNode(ptr->val);
        root->left = construct(sz / 2, head);
        root->right = construct(sz - sz / 2 - 1, ptr->next);
        return root;
    }
    
    TreeNode *sortedListToBST(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (head == NULL) return NULL;
        int sz = 0;
        ListNode *ptr = head;
        while (ptr) {
            sz ++;
            ptr = ptr->next;
        }
        return construct(sz, head);
    }
};
