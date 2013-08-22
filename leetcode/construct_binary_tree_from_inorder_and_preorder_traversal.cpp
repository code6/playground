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
    TreeNode *_buildTree(vector<int> &inorder, int ib, int ie, 
        vector<int> &preorder, int pb, int pe) {            
            if (ib > ie) {
                return NULL;
            }
            
            TreeNode *root = new TreeNode(preorder[pb]);
            int ipos;
            for (ipos = ib; ipos <= ie; ipos++) {
                if (inorder[ipos] == root->val) break;
            }
            root->left = _buildTree(inorder, ib, ipos - 1,
                preorder, pb + 1, pb + 1 + (ipos - ib) - 1);
            root->right = _buildTree(inorder, ipos + 1, ie, 
                preorder,  pb + ipos - ib + 1 , pe);
            return root;            
        }
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return _buildTree(inorder, 0, (int)inorder.size() - 1,
            preorder, 0, (int)preorder.size() - 1);
    }
};
