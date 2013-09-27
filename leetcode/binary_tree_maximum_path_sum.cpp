/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
#define mp make_pair
typedef pair<int, int> PII;
class Solution {
public:
    
    PII mps(TreeNode *root) {
        if (root == NULL) {
            return mp(INT_MIN, 0);
        }
        PII ret;
        PII le = mps(root->left);
        PII ri = mps(root->right);        
        ret.first = root->val;
        if (le.second > 0) ret.first += le.second;
        if (ri.second > 0) ret.first += ri.second;
        ret.first = max(ret.first, max(le.first, ri.first));
        ret.second = root->val + max(0, max(le.second, ri.second));
        return ret;
    }
    
    int maxPathSum(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        return mps(root).first;
    }
};
