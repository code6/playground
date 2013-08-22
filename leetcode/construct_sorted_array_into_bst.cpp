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
    
    TreeNode *construct(int f, int r, vector<int>&num) {
        if (f > r) {
            return NULL;
        }
        int mid = (f + r) / 2;
        
        TreeNode *root = new TreeNode(num[mid]);
        root->left = construct(f, mid - 1, num);
        root->right = construct(mid + 1, r, num);
        return root;
    }
    TreeNode *sortedArrayToBST(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        if (num.size() == 0) {
            return NULL;
        }
        
        return construct(0, num.size() - 1, num);
    }
};
