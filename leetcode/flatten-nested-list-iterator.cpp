// https://leetcode.com/problems/flatten-nested-list-iterator/

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
    
    struct Context {
        vector<NestedInteger> &items;
        int pos;
        
        int next() {
            return items[pos++].getInteger();
        }
        
        vector<NestedInteger>& enter() {
            return items[pos++].getList();
        }
        
        bool isInteger() {
            return items[pos].isInteger();
        }
        
        explicit operator bool() {
            return pos < items.size();
        }
    };
    
    stack<Context> stuff;
    
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        stuff.push(Context{nestedList, 0});
    }

    int next() {
        if (!hasNext()) {
            return -1;
        }
        return stuff.top().next();
    }

    bool hasNext() {
        while (!stuff.empty()) {
            Context& cur = stuff.top();
            
            if (cur) {
                if (cur.isInteger()) {
                    return true;
                } else {
                    stuff.push(Context{cur.enter(), 0});
                }
            } else {
                stuff.pop();
            }
        }
        
        return false;
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
