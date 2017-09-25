// https://leetcode.com/problems/student-attendance-record-ii/

class Solution {
    
    static const int MOD = 1000000000 + 7;
    
    int mem[3][2][100001];
    
public:
    int checkRecord(int n) {
        memset(mem, -1, sizeof mem);
        
        // must grow DP from smaller cases
        // because recursion is too deep
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i >= 0; --i)
                for (int j = 0; j < 3; ++j)
                    work(k, i, j);
        
        return work(n, true, 0);
    }
    
    int64_t work(int len, bool canA, int preL) {
        if (len <= 0)
            return 1;
        
        auto& ans = mem[preL][canA][len];
        if (ans != -1)
            return ans;
        
        int64_t sub = 0;
        
        // can always do P
            sub += work(len-1, canA, 0);
        if (canA)
            sub += work(len-1, false, 0);
        if (preL < 2)
            sub += work(len-1, canA, preL+1);
        
        return ans = sub % MOD;
    }
};
