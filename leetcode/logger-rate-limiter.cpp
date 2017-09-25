// https://leetcode.com/problems/logger-rate-limiter/

class Logger {
    unordered_map<string, int> m;
public:
    /** Initialize your data structure here. */
    Logger() {
    }
    
    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
        If this method returns false, the message will not be printed.
        The timestamp is in seconds granularity. */
    bool shouldPrintMessage(int t2, string message) {
        auto it = m.find(message);
        if (it == m.end() || t2 - it->second >= 10) return m[message]=t2, true;
        return false;
    }
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger obj = new Logger();
 * bool param_1 = obj.shouldPrintMessage(timestamp,message);
 */
