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
    
    int height(TreeNode *root) {
        //return -1 if the node is not balanced
        if (root == NULL) {
            return 0;
        }
        int lt = height(root->left);
        int rt = height(root->right);
        if (lt == -1 || rt == -1) {
            return -1;
        }
        if (abs(lt - rt) <= 1) {
            return max(lt, rt) + 1;
        } {
            return -1;
        }
    }
    bool isBalanced(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return height(root) != -1;
    }
};
