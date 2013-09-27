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
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > ret;
        if (root == NULL) return ret;
        
        queue<TreeNode *> que;        
        que.push(root);
        int f, ff, r;
        f = ff = 0; r = 1;
        while (f < r) {
            ff = r;
            vector<int> cur_level;
            while (f < ff) {
                f++;
                TreeNode *cur_node = que.front();
                que.pop();
                cur_level.push_back(cur_node->val);
                if (cur_node->left) {
                    que.push(cur_node->left);
                    r++;
                }
                if (cur_node->right) {
                    que.push(cur_node->right);
                    r++;
                }                
            }
            ret.push_back(cur_level);
        }
        
        for (int i = 0; i < ret.size() / 2; i++) swap(ret[i], ret[ret.size() - 1 - i]);
        
        return ret;
        
    }
};
