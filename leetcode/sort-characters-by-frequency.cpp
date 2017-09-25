// https://leetcode.com/problems/sort-characters-by-frequency/

struct Entry {
    int n;
    char c;
    bool operator<(Entry e) const {
        return  n < e.n;
    }
};

class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> m;
        for (char c : s)
            m[c] += 1;
        priority_queue<Entry> q;
        for (auto p : m)
            q.push(Entry{p.second, p.first});
        string ans;
        while (!q.empty()) {
            auto e = q.top();
            q.pop();
            for (int i = 0; i < e.n; ++i) {
                ans += e.c;
            }
        }
        return ans;
    }
};
