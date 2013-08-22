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
    void flatten(TreeNode *root) {
        flat(root);
    }

    TreeNode *flat(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL) {
            return NULL;
        }
        
        TreeNode *lefttail = flat(root->left);
        TreeNode *righttail = flat(root->right);
        
        if (lefttail) {
            lefttail->right = root->right;
        }
        
        if (root->left) {
            root->right = root->left;
            root->left = NULL;
        }
        
        if (righttail) return righttail;
        if (lefttail) return lefttail;
        return root;

    }
};
