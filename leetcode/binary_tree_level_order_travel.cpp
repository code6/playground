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
    vector<vector<int> > levelOrder(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        vector<vector<int> > ret;
        
        if (root == NULL) return ret;
        
        vector<TreeNode*> que;
        int f, r, rr;
        f = 0; r = rr = 1;
        que.push_back(root);
        
        while (f < r) {
            vector<int> row;
            int i;
            for (; f < rr; f++) {
                TreeNode *cur = que[f];
                row.push_back(cur->val);
                if (cur->left) {
                    que.push_back(cur->left);
                    r++;
                }
                if (cur->right) {
                    que.push_back(cur->right);
                    r++;
                }
            }
            ret.push_back(row);
            rr = r;
        }        
        return ret;
    }
};
