// https://leetcode.com/problems/word-pattern/

class Solution {
public:
    bool wordPattern(string pattern, string str) {
        map<char, int> cp;
        map<string, int> cs;
        istringstream big { str };
        
        int i = 0;
        for (string w; big >> w; ++i) {
            if (work(cp, pattern[i]) != work(cs, w)) {
                return false;
            }
        }
        return i == pattern.size();
    }
    
    template <typename T>
    static int work(map<T, int> &m, const T &e) {
        auto it = m.find(e);
        if (it == m.end()) {
            int k = m.size();
            m[e] = k;
            return k;
        } else {
            return it->second;
        }
    }
};
