// https://leetcode.com/problems/reverse-words-in-a-string/

int clean_spaces(string &s) {
    if (s.empty()) return 0;

    int wc = 0;
    char *o = &s[0];
    char *i = &s[0];

    while (*i == ' ')
        ++i;
    
    while (*i) {
        while (*i && *i != ' ')
            *o++ = *i++;
        
        ++wc;
        
        while (*i == ' ')
            ++i;
        
        if (*i)
            *o++ = ' ';
    }

    s.erase(o - &s[0]);

    return wc;
}

struct span {
    int i, j;

    int size() {
        return j - i;
    }

    bool operator<(span s) const {
        return i < s.i;
    }
};

span find_word(const string &s, int i) {
    int j = i;
    while (j < s.size() && s[j] != ' ') {
        ++j;
    }
    return {i, j};
}

void swap_words(string &s, span w1, span w2) {
    auto it = s.begin();
    rotate(it + w1.i, it + w2.i, it + w2.j);
    rotate(it + w1.i + w2.size(), it + w2.j - 1, it + w2.j);
}

void reverse_words(string &s) {
    int wc = clean_spaces(s);

    for (int k = 1; k < wc; ++k) {
        int i = 0;
        for (int t = 0; t < wc - k; ++t) {
            auto w1 = find_word(s, i);
            auto w2 = find_word(s, w1.j + 1);

            swap_words(s, w1, w2);

            i += w2.size() + 1;
        }
    }
}

class Solution {
public:

    void reverseWords(string &s) {
        reverse_words(s);
    }
};
