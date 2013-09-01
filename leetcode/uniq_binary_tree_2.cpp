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
    
    vector<TreeNode *> rec_gen(int f, int r) {
        vector<TreeNode *> res;
        if (f > r) {
            res.push_back(NULL);
            return res;
        }
        
        for (int rval = f; rval <= r; rval++) {
            vector<TreeNode *> le_list = rec_gen(f, rval - 1);
            vector<TreeNode *> ri_list = rec_gen(rval + 1, r);
            for (int i = 0; i < le_list.size(); i++) {
                for (int j = 0; j < ri_list.size(); j++) {
                    TreeNode *root = new TreeNode(rval);
                    root->left = le_list[i];
                    root->right = ri_list[j];
                    res.push_back(root);
                }
            }
        }
        
        return res;
    }
    
    vector<TreeNode *> generateTrees(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        vector<TreeNode *> ret;
        ret = rec_gen(1, n);
        
        return ret;
    }
};
