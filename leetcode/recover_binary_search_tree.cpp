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
    void inorderRecover(TreeNode *root, TreeNode *& last_pos, 
    TreeNode *& first_pos, TreeNode *& second_pos) {
        if (root == NULL) {
            return;
        }
        inorderRecover(root->left, last_pos, first_pos, second_pos);
        if (last_pos && root->val < last_pos->val) {
            if (first_pos == NULL) {
                first_pos = last_pos;
            }
            second_pos = root;
        }
        last_pos = root;
        inorderRecover(root->right, last_pos, first_pos, second_pos);
        if (last_pos && root->val > last_pos->val) {
            if (first_pos == NULL) {
                first_pos = root;
            }
            second_pos = last_pos;
        }
    }
    void recoverTree(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        TreeNode *first_pos;
        TreeNode *second_pos;
        TreeNode *last_pos;
        
        first_pos = second_pos = last_pos = NULL;
        
        inorderRecover(root, last_pos, first_pos, second_pos);
        
        if (first_pos && second_pos) {
            swap(first_pos->val, second_pos->val);
        }
    }
};
