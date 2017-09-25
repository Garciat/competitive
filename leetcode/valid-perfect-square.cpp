// https://leetcode.com/problems/valid-perfect-square/

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
    bool isPerfectSquare(int num) {
        auto pred = [num](int x) { return x < num / x; };
        auto it = partition_point(number_iter{1}, number_iter{num}, pred);
        auto x = *it;
        return x * x == num;
    }
};
