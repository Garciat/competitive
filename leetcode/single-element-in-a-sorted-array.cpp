// https://leetcode.com/problems/single-element-in-a-sorted-array/

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
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        auto pred = [&nums] (int i) { return nums[2*i] == nums[2*i+1]; };
        auto it = partition_point(number_iter{0}, number_iter{n/2}, pred);
        return nums[2 * (*it)];
    }
};
