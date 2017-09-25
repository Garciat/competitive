// https://leetcode.com/problems/merge-intervals/

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
    vector<Interval> merge(vector<Interval>& intervals) {
        if (intervals.empty()) return {};
        
        sort(begin(intervals), end(intervals), [] (Interval a, Interval b) {
            if (a.start == b.start) return a.end < b.end;
            return a.start < b.start;
        });
        
        vector<Interval> ans;
        auto curr = intervals[0];
        
        for (int i = 0; i < intervals.size(); ++i) {
            if (intervals[i].start > curr.end) {
                ans.push_back(curr);
                curr = intervals[i];
            } else {
                curr.end = max(curr.end, intervals[i].end);
            }
        }
        
        ans.push_back(curr);
        
        return ans;
    }
};
