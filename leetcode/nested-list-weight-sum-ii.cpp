// https://leetcode.com/problems/nested-list-weight-sum-ii/

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
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        unordered_map<int, int> m;
        int md = work(m, nestedList, 1);
        int ans = 0;
        for (auto p : m) {
            ans += (md - p.first + 1) * p.second;
        }
        return ans;
    }
    
    int work(unordered_map<int, int> &m, const vector<NestedInteger>& ns, int depth) {
        int s = 0;
        int md = depth;
        for (auto& n : ns) {
            if (n.isInteger()) {
                s += n.getInteger();
            } else {
                int d = work(m, n.getList(), depth+1);
                md = max(md, d);
            }
        }
        m[depth] += s;
        return md;
    }
};

