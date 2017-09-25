// https://leetcode.com/problems/mini-parser/

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
    NestedInteger deserialize(string s) {
        int i = 0;
        return work(s, i);
    }
    
    NestedInteger work(string s, int &i) {
        NestedInteger n;
        if (s[i] == '[') {
            i += 1;
            while (s[i] != ']') {
                n.add(work(s, i));
                if (s[i] == ',')
                    i += 1;
            }
            i += 1;
        } else {
            long long val = 0;
            int sign = 1;
            if (s[i] == '-') {
                sign = -1;
                i += 1;
            }
            while (s[i] != ',' && s[i] != ']' && s[i] != '\0') {
                val *= 10;
                val += s[i] - '0';
                i += 1;
            }
            n.setInteger(sign * val);
        }
        return n;
    }
};
