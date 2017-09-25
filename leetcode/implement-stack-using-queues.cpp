// https://leetcode.com/problems/implement-stack-using-queues/

class MyStack {
    
    queue<int> p, q;
    
public:
    /** Initialize your data structure here. */
    MyStack() {
        
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        p.push(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        if (q.empty()) {
            for (;;) {
                int x = p.front();
                p.pop();
                if (p.empty()) {
                    p.push(x);
                    break;
                } else {
                    q.push(x);
                }
            }
            swap(p, q);
        }
        int x = q.front();
        q.pop();
        return x;
    }
    
    /** Get the top element. */
    int top() {
        int x = pop();
        push(x);
        return x;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return p.empty() && q.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack obj = new MyStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.top();
 * bool param_4 = obj.empty();
 */
