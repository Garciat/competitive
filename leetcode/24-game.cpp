// https://leetcode.com/problems/24-game/

struct Quot {
    int a, b;
    
    Quot(int a) : a{a}, b{1}
    { }
    
    Quot(int a, int b) : a{a}, b{b}
    { }
    
    Quot operator+(Quot rhs) const {
        return Quot{a*rhs.b + rhs.a*b, b*rhs.b};
    }
    
    Quot operator-(Quot rhs) const {
        return Quot{a*rhs.b - rhs.a*b, b*rhs.b};
    }
    
    Quot operator*(Quot rhs) const {
        return Quot{a*rhs.a, b*rhs.b};
    }
    
    Quot operator/(Quot rhs) const {
        return Quot{a*rhs.b, b*rhs.a};
    }
    
    bool is_ok() const {
        if (b == 0) return false;
        // cout << a << '/' << b << endl;
        return a / b == 24 && a % b == 0;
    }
};

Quot op(Quot a, Quot b, int i) {
    switch (i) {
    case 0:
        return a + b;
    case 1:
        return a - b;
    case 2:
        return a * b;
    case 3:
        return a / b;
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
                    if (hello(nums, i, j, k)) {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
    
    bool hello(vector<int>& nums, int i, int j, int k) {
        return op(op(op(nums[0], nums[1], i), nums[2], j), nums[3], k).is_ok()
            || op(op(nums[0], nums[1], i), op(nums[2], nums[3], j), k).is_ok()
            || op(nums[0], op(nums[1], op(nums[2], nums[3], i), j), k).is_ok();
    }
};
