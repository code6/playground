/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

bool cmp(const Interval &a, const Interval & b) {
    if (a.start != b.start) {
        return a.start < b.start;
    }
    return a.end < b.end;
}
 
class Solution {
public:
    bool intersect(Interval a, Interval b) {
        return !(a.end < b.start || a.start > b.end);
    }
    void merge(Interval &a, Interval b) {
        a.start = min(a.start, b.start);
        a.end = max(a.end, b.end);
    }
    vector<Interval> merge(vector<Interval> &intervals) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (intervals.size() <= 1) {
            return intervals;
        }
        
        sort(intervals.begin(), intervals.end(), cmp);
        
        vector<Interval> ret;
        
        int i, j;
        for (i = 0; i < intervals.size(); i++) {
            Interval cur = intervals[i];
            for (j = i + 1; j < intervals.size(); j++) {
                if (intersect(cur, intervals[j])) {
                    merge(cur, intervals[j]);
                } else {
                    break;
                }
            }
            i = j - 1;
            ret.push_back(cur);
        }
        
        return ret;
    }
};
