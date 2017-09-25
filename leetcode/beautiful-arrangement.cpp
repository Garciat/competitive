// https://leetcode.com/problems/beautiful-arrangement/

class Solution {
public:
    int countArrangement(int N) {
        array<bool, 15> used {};
        return work(N, 1, used);
    }
    
    int work(int N, int i, array<bool, 15> &used) {
        if (i > N) return 1;
        
        int ans = 0;
        for (int k = 1; k <= N; ++k) {
            if (used[k - 1])
                continue;
            
            if (i % k != 0 && k % i != 0)
                continue;
            
            used[k-1] = true;
            int tmp = work(N, i+1, used);
            used[k-1] = false;
            
            ans += tmp;
        }
        
        return ans;
    }
};
