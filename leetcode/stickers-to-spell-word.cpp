// https://leetcode.com/problems/stickers-to-spell-word/

using letter_count = array<int, 27>;

namespace std {
    template <>
    struct hash<letter_count>
    {
        std::size_t operator()(const letter_count& k) const
        {
            size_t h = 0;

            for (int x : k) {
                h = (h + (324723947 + x)) ^ 93485734985;
            }

            return h;
        }
    };
}

letter_count operator-(const letter_count& c, const letter_count& d) {
    letter_count ans{};
    for (int i = 0; i < ans.size(); ++i) {
        ans[i] = max(0, c[i] - d[i]);
    }
    return ans;
}

bool is_done(const letter_count &c) {
    for (int x : c) {
        if (x > 0) return false;
    }
    return true;
}

bool contributes(const letter_count &tgt, const letter_count &c) {
    for (int i = 0; i < tgt.size(); ++i) {
        if (tgt[i] && c[i]) return true;
    }
    return false;
}

void print(letter_count c) {
    for (int x : c) cout << x << ' ';
    cout << endl;
}

class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        
        letter_count total_count{};
        
        vector<letter_count> counts(stickers.size(), letter_count{});
        
        for (int i = 0; i < stickers.size(); ++i) {
            for (char c : stickers[i]) {
                counts[i][c-'a'] += 1;
                total_count[c-'a'] += 1;
            }
        }
        
        letter_count needed{};
        
        for (char c : target) {
            needed[c-'a'] += 1;
            if (total_count[c-'a'] == 0) {
                return -1;
            }
        }
        
        return solve(counts, needed);
    }
    
    unordered_map<letter_count, int> memo;
    
    int solve(vector<letter_count> &counts, letter_count target) {
        if (is_done(target)) return 0;
        int& ans = memo[target];
        if (ans != 0) return ans;
        int tmp = 1000;
        for (auto&& c : counts) {
            if (contributes(target, c))
                tmp = min(tmp, solve(counts, target - c));
        }
        return ans = 1 + tmp;
    }
};
