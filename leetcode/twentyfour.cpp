// https://leetcode.com/problems/24-game/

std::function<double(double, double)> op(int i) {
    switch (i) {
    case 0:
        return [] (double x, double y) { return x + y; };
    case 1:
        return [] (double x, double y) { return x - y; };
    case 2:
        return [] (double x, double y) { return x * y; };
    case 3:
        return [] (double x, double y) { return y == 0 ? INT_MAX : x / y; };
    }
}

class Solution {
public:
    bool judgePoint24(vector<int>& nums) {
        sort(begin(nums), end(nums));
        
        do {
            if (work(nums)) {
                return true;
            }
        } while (next_permutation(begin(nums), end(nums)));
        
        return false;
    }
    
    bool work(vector<int>& nums) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < 4; ++k) {
                    if (hello(nums[0], nums[1], nums[2], nums[3], op(i), op(j), op(k))) {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
    
    template <typename Func>
    bool hello(int x, int y, int z, int w, Func f, Func g, Func h) {
        return f(g(h(x, y), z), w) == 24
            || f(g(x, y), h(z, w)) == 24
            || f(x, g(y, h(z, w))) == 24;
    }
};
