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
    int maxDepth(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL) {
            return 0;
        }

        if (root->left == NULL && root->right == NULL) {
            return 1;
        }

        int ret = 0;

        if (root->left) {
            ret = max(ret, maxDepth(root->left));
        }

        if (root->right) {
            ret = max(ret, maxDepth(root->right));
        }

        ret += 1;

        return ret;
    }
};
