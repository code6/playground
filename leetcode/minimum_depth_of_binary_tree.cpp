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
    int minDepth(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL) {
            return 0;
        }
        
        if (root->left == NULL && root->right == NULL) {
            return 1;
        }
        
        int ret = INT_MAX;
        
        if (root->left) {
            ret = min(ret, minDepth(root->left));
        }
        
        if (root->right) {
            ret = min(ret, minDepth(root->right));
        }
        
        ret += 1;
        
        return ret;
    }
};
