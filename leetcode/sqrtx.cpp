// https://leetcode.com/problems/sqrtx/

struct number_iter {
    int val;
    bool operator ==(number_iter rhs) {
        return val == rhs.val;
    }
    bool operator !=(number_iter rhs) {
        return val != rhs.val;
    }
    number_iter& operator++() {
        ++val;
        return *this;
    }
    int operator*() {
        return val;
    }
    int operator-(number_iter rhs) {
        return val - rhs.val;
    }
    number_iter& operator+=(int x) {
        val += x;
        return *this;
    }
};

// This is the tricky part:

namespace std {
    template <>
    struct iterator_traits<number_iter> {
        using difference_type = int;
        using iterator_category = random_access_iterator_tag;
    };
}

class Solution {
public:
    int mySqrt(int x) {
        assert(x >= 0);
        if (x == 0) return 0;
        if (x == 1) return 1;
        auto pred = [x](int y) { return y <= x / y; };
        auto it = partition_point(number_iter{1}, number_iter{x}, pred);
        return *it - 1;
    }
};
