// https://leetcode.com/problems/student-attendance-record-i/

class Solution {
public:
    bool checkRecord(string s) {
        auto firstA = s.find('A');
        if (firstA != string::npos) {
            if (s.find('A', firstA + 1) != string::npos) {
                return false;
            }
        }
        
        return s.find("LLL") == string::npos;
    }
};
