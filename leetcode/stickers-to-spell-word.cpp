// https://leetcode.com/problems/stickers-to-spell-word/

struct ordered_letter_set {
    
    void insert(char c) {
        counts[c - 'a'] += 1;
    }
    
    bool empty() const {
        for (int x : counts) {
            if (x > 0) return false;
        }
        return true;
    }
    
    bool contains(char c) const {
        return counts[c - 'a'];
    }
    
    bool has_empty_intersect(const ordered_letter_set &rhs) const {
        for (int i = 0; i < counts.size(); ++i) {
            if (counts[i] && rhs.counts[i])
                return false;
        }
        return true;
    }
    
    friend ordered_letter_set operator-(const ordered_letter_set& c, const ordered_letter_set& d) {
        ordered_letter_set ans{};
        for (int i = 0; i < ans.counts.size(); ++i) {
            ans.counts[i] = max(0, c.counts[i] - d.counts[i]);
        }
        return ans;
    }
    
    friend bool operator==(const ordered_letter_set& c, const ordered_letter_set& d) {
        return c.counts == d.counts;
    }
    
    array<int, 26> counts;
};


namespace std {
    template <>
    struct hash<ordered_letter_set>
    {
        std::size_t operator()(const ordered_letter_set& k) const
        {
            size_t h = 0;
            for (int x : k.counts)
                h = (h + (324723947 + x)) ^ 93485734985;
            return h;
        }
    };
}


class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        
        ordered_letter_set all_letters{};
        
        vector<ordered_letter_set> word_letters(stickers.size(), ordered_letter_set{});
        
        for (int i = 0; i < stickers.size(); ++i) {
            for (char c : stickers[i]) {
                word_letters[i].insert(c);
                all_letters.insert(c);
            }
        }
        
        ordered_letter_set needed{};
        
        for (char c : target) {
            needed.insert(c);
            if (!all_letters.contains(c)) {
                return -1;
            }
        }
        
        return solve(word_letters, needed);
    }
    
    unordered_map<ordered_letter_set, int> memo;
    
    int solve(vector<ordered_letter_set> &word_letters, ordered_letter_set needed) {
        if (needed.empty()) return 0;
        
        int& ans = memo[needed];
        if (ans != 0) return ans;
        
        int tmp = 1000;
        for (auto&& candidate : word_letters) {
            if (!needed.has_empty_intersect(candidate))
                tmp = min(tmp, solve(word_letters, needed - candidate));
        }
        
        return ans = 1 + tmp;
    }
};
