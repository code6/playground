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
    TreeNode *build(ListNode *& head, int n) {
        if (n <= 0) {
            return NULL;
        }
        int mid = n / 2;
        TreeNode *left = build(head, mid);
        TreeNode *root = new TreeNode(head->val);
        root->left = left;
        head = head->next;
        root->right = build(head, n - mid  - 1);
        return root;
    }
    TreeNode *sortedListToBST(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int len = 0;
        ListNode *ptr = head;
        while (ptr) len ++, ptr = ptr->next;
        if (len == 0) return NULL;
        return build(head, len);
    }
};
