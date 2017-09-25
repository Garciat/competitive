// https://leetcode.com/problems/judge-route-circle/

class Solution {
public:
    bool judgeCircle(string moves) {
        int64_t x = 0;
        int64_t y = 0;
        
        for (char m : moves) {
            switch (m) {
                case 'U':
                    y += 1;
                    break;
                case 'D':
                    y -= 1;
                    break;
                case 'L':
                    x -= 1;
                    break;
                case 'R':
                    x += 1;
                    break;
            }
        }
        
        return x == 0 && y == 0;
    }
};
