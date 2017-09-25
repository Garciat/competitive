// https://leetcode.com/problems/moving-average-from-data-stream/

class MovingAverage {
public:
    deque<int> xs;
    int s;
    int m;
    
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        s = 0;
        m = size;
    }
    
    double next(int val) {
        s += val;
        xs.push_back(val);
        if (xs.size() > m) {
            s -= xs.front();
            xs.pop_front();
        }
        return (double)s / xs.size();
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param_1 = obj.next(val);
 */
