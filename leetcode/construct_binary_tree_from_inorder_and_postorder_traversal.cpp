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
        vector<int> &postorder, int pb, int pe) {            
            if (ib > ie) {
                return NULL;
            }
            
            TreeNode *root = new TreeNode(postorder[pe]);
            int ipos;
            for (ipos = ib; ipos <= ie; ipos++) {
                if (inorder[ipos] == root->val) break;
            }
            root->left = _buildTree(inorder, ib, ipos - 1,
                postorder, pb, pb + (ipos - ib) - 1);
            root->right = _buildTree(inorder, ipos + 1, ie, 
                postorder, pb + (ipos - ib), pe - 1);
            return root;            
        }
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        if (inorder.size() == 0) return NULL;
        
        return _buildTree(inorder, 0, inorder.size() - 1, 
            postorder, 0, postorder.size() - 1);        
    }
};
