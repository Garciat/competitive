// https://leetcode.com/problems/arranging-coins/

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

namespace std {
    template <>
    struct iterator_traits<number_iter> {
        using difference_type = int;
        using iterator_category = random_access_iterator_tag;
    };
}

class Solution {
public:
    int arrangeCoins(int n) {
        if (n == 1) return 1;
        auto it = partition_point(number_iter{1}, number_iter{n}, [n](long long x) { return x*(x+1)/2<=n; });
        return *it - 1;
    }
};
