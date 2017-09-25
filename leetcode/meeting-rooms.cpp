// https://leetcode.com/problems/meeting-rooms/

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
    bool canAttendMeetings(vector<Interval>& intervals) {
        sort(begin(intervals), end(intervals), [] (Interval a, Interval b) {
            return a.start < b.start;
        });
        
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i-1].end > intervals[i].start) {
                return false;
            }
        }
        
        return true;
    }
};
