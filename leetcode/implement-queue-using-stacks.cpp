// https://leetcode.com/problems/implement-queue-using-stacks/

class MyQueue {
    
    stack<int> p, q;
    
public:
    /** Initialize your data structure here. */
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        p.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        peek();
        int x = q.top();
        q.pop();
        return x;
    }
    
    /** Get the front element. */
    int peek() {
        if (q.empty()) {
            while (!p.empty()) {
                q.push(p.top());
                p.pop();
            }
        }
        return q.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return p.empty() && q.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue obj = new MyQueue();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.peek();
 * bool param_4 = obj.empty();
 */
