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
    vector<int> inorderTraversal(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> ret;
        if (root) {
            vector<int> tmp = inorderTraversal(root->left);
            ret.insert(ret.end(), tmp.begin(), tmp.end());
            tmp = inorderTraversal(root->right);
            ret.push_back(root->val);
            ret.insert(ret.end(), tmp.begin(), tmp.end());
            
        } else {
            return ret;
        }
        
    }
};
