// https://leetcode.com/problems/insert-interval/

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
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        auto x = lower_bound(begin(intervals), end(intervals), newInterval, [](Interval a, Interval b) {
            return a.end < b.start;
        });
        
        auto y = upper_bound(begin(intervals), end(intervals), newInterval, [](Interval a, Interval b) {
            return a.end < b.end;
        });
        if (y != end(intervals)) {
            if (y->start <= newInterval.end && newInterval.end < y->end) {
                ++y;
            }
        }
        
        vector<Interval> ans;
        
        for (auto it = begin(intervals); it != x; ++it) {
            ans.push_back(*it);
        }
        
        auto xx = x;
        
        while (x != y) {
            xx->end = x->end;
            ++x;
        }
        
        if (x != xx) {
            xx->start = min(xx->start, newInterval.start);
            xx->end = max(xx->end, newInterval.end);
            ans.push_back(*xx);
        } else {
            ans.push_back(newInterval);
        }
        
        for (auto it = y; it != end(intervals); ++it) {
            ans.push_back(*it);
        }
        
        return ans;
    }
};
