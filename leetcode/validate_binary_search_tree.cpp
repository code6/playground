/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
typedef pair<int, int> PII;
#define mp make_pair

class Solution {
public:

    PII checkBSTLimit(TreeNode *root) {
        PII ret = mp(root->val, root->val);
        if (root->left) {
            PII le = checkBSTLimit(root->left);
            if (le.first == INT_MIN) {
                return le;
            }
            if (le.second >= ret.first) {
                return mp(INT_MIN, INT_MIN);
            }
            ret.first = le.first;
        }
        if (root->right) {
            PII ri = checkBSTLimit(root->right);
            if (ri.first == INT_MIN) {
                return ri;
            }
            if (ri.first <= ret.second) {
                return mp(INT_MIN, INT_MIN);
            }
            ret.second = ri.second;
        }
        return ret;
    }
    
    bool isValidBST(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL) return true;
        PII limit = checkBSTLimit(root);
        return limit.first != INT_MIN;
    }
};
