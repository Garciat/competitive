// https://leetcode.com/problems/replace-words/

struct Trie {
    Trie *next[26];
    int words;
    
    Trie() {
        fill(begin(next), end(next), nullptr);
        words = 0;
    }
    
    void add(const string& word, int i = 0) {
        auto t = next[word[i] - 'a'];
        
        if (t == nullptr) {
            t = next[word[i] - 'a'] = new Trie;
        }
        
        if (word[i+1] == '\0' || word[i+1] == ' ') {
            t->words += 1;
        } else {
            t->add(word, i + 1);
        }
    }
};

class Solution {
public:
    string replaceWords(vector<string>& dict, string s) {
        Trie t;
        for (auto&& word : dict) {
            t.add(word);
        }
        
        int out = 0;
        int i = 0;
        
        for (;;) {
            while (s[i] && s[i] == ' ') {
                s[out++] = s[i++];
            }
            
            if (!s[i]) {
                break;
            }
            
            Trie *u = &t;
            while (s[i] && s[i] != ' ') {
                u = u->next[s[i] - 'a'];
                s[out++] = s[i++];
                if (!u || u->words) break;
            }
            
            
            while (s[i] && s[i] != ' ') {
                if (!u)
                    s[out++] = s[i];
                i += 1;
            }
        }
        
        s.erase(out);
        
        return s;
    }
};
