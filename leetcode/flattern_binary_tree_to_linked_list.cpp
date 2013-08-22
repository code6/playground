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
    TreeNode *_flatten(TreeNode *root) {
        if (root == NULL) {
            return NULL;
        }
        TreeNode *lt = _flatten(root->left);
        TreeNode *rt = _flatten(root->right);
        root->left = NULL;
        root->right = lt;
        TreeNode *ptr = root;
        while (ptr->right) ptr = ptr->right;
        ptr->right = rt;
        return root;
    }
    void flatten(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        _flatten(root);
    }
};
