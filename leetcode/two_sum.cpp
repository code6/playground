#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<pair<int,int> > vp;
    vector<int> twoSum(vector<int> &numbers, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
		vp.clear();
        
        for (int i = 0; i < numbers.size(); i++) {
            vp.push_back(make_pair(numbers[i], i));
        }
        
        sort(vp.begin(), vp.end());
        
        vector<int> ret;
        for (int f = 0; f < vp.size() - 1; f++) {
            int r = lower_bound(vp.begin() + f + 1, vp.end(), make_pair(target - vp[f].first, -1)) - vp.begin();
            if (r < vp.size() && vp[r].first + vp[f].first == target) {
                ret.push_back(vp[f].second + 1);
                ret.push_back(vp[r].second + 1);
                sort(ret.begin(), ret.end());
                break;
            }
            
        }
        return ret;
    }
};

int main(int argc, char *argv[]) {
	int arr[] = {678,227,764,37,956,982,118,212,177,597,519,968,866,121,771,343,561};
	vector<int> numbers(arr , arr + sizeof(arr) / sizeof(int));
	Solution sol = Solution();
	vector<int> res = sol.twoSum(numbers, 295);
	cout<< res[0] << ' ' << res[1] << endl;
	
}