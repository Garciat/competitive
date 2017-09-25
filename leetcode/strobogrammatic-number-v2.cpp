// https://leetcode.com/problems/strobogrammatic-number/

template <typename InputIter, typename Func>
struct mapped_iterator {
    InputIter iter;
    Func mapper;
    
    mapped_iterator(InputIter iter, Func mapper)
        : iter{iter}, mapper{mapper}
    { }
    
    mapped_iterator& operator++() {
        ++iter;
        return *this;
    }
    
    auto operator*() -> decltype(mapper(*iter)) {
        return mapper(*iter);
    }
};

namespace std {
    template <typename InputIter, typename Func>
    struct iterator_traits<mapped_iterator<InputIter, Func>> {
        using value_type = decltype(declval<Func>()(*declval<InputIter>()));
    };
}


template <typename InputIter, typename Func>
mapped_iterator<InputIter, Func> map_iterator(InputIter iter, Func mapper) {
    return {iter, mapper};
}

char digit_mirror(char c) {
    switch (c) {
    case '0': return '0';
    case '1': return '1';
    case '6': return '9';
    case '8': return '8';
    case '9': return '6';
    default:  return '*';
    }
}

class Solution {
public:
    bool isStrobogrammatic(string num) {
        return equal(num.begin(), num.end(), map_iterator(num.rbegin(), digit_mirror));
    }
};
