// https://leetcode.com/problems/guess-number-higher-or-lower/

/*

algo:
    
    binary search:
        left = 1, right = n
        until right:
            try with guess = left + (right - left) / 2
            (this formula makes right exclusive... so actually start with right = n + 1)
            if ans =  0 done
               ans = -1 retry with right=guess
               ans = +1 retry with left=guess

*/

int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        int L = 1;
        int R = n + 1;
        
        for (;;) {
            int g = L + (R - L) / 2;
            
            switch (guess(g)) {
            case 0:
                return g;
            case 1:
                L = g;
                break;
            case -1:
                R = g;
                break;
            }
        }
    }
};
