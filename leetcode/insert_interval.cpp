/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    bool intersect(Interval a, Interval b) {
        return !(a.end < b.start || a.start > b.end);
    }
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<Interval> ret;
        
        if (intervals.size() == 0) {
            ret.push_back(newInterval);
            return ret;
        }
        
        if (newInterval.end < intervals[0].start) {
            ret.push_back(newInterval);
            for (int i = 0; i < intervals.size(); i++) {
                ret.push_back(intervals[i]);
            }
            return ret;
        }
        
        if (newInterval.start > intervals[intervals.size() - 1].end) {
            intervals.push_back(newInterval);
            return intervals;
        }
        
        for (int i = 0; i < intervals.size(); i++) {
            if (i && intervals[i - 1].end < newInterval.start && intervals[i].start > newInterval.end) {
                    ret.push_back(newInterval);
                }
            if (intersect(intervals[i], newInterval)) {
                Interval comb;
                comb.start = min(intervals[i].start, newInterval.start);
                while (i < intervals.size() && intersect(intervals[i], newInterval)) {
                    i++;    
                }
                i --;
                comb.end = max(intervals[i].end, newInterval.end);
                ret.push_back(comb);
                
            } else {
                ret.push_back(intervals[i]);
            }
        }
        
        
        return ret;
    }
};
