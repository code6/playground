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
    bool is_leaf(TreeNode *root) {
        return root != NULL && root->left == NULL && root->right == NULL;
    }
    bool _hasPathSum(TreeNode *root, int sum) {
        
        if (root == NULL) {
            return false;
        }
        
        if (is_leaf(root)) {
            return sum == root->val;
        } else {
            if (root->left && _hasPathSum(root->left, sum - root->val)) {
                return true;
            }
            
            if(root->right && _hasPathSum(root->right, sum - root->val)) {
                return true;
            }        
            return false;
        }
    }
    
    bool hasPathSum(TreeNode *root, int sum) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return _hasPathSum(root, sum);
    }
};
