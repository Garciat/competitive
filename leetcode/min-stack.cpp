// https://leetcode.com/problems/min-stack/

class MinStack {
    stack<int> xs;
    multiset<int> ys;
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        xs.push(x);
        ys.insert(x);
    }
    
    void pop() {
        ys.erase(ys.find(xs.top()));
        xs.pop();
    }
    
    int top() {
        return xs.top();
    }
    
    int getMin() {
        return *ys.begin();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
