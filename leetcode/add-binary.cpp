// https://leetcode.com/problems/add-binary/

class Solution {
public:
    string addBinary(string a, string b) {
        if (!a.size() && !b.size()) {
            return "0";
        }
        
        string r;
        
        int p1 = a.size() - 1;
        int p2 = b.size() - 1;
        
        int c = 0;
        
        while (p1 >= 0 && p2 >= 0) {
            if (a[p1] == b[p2]) {
                r += '0' + c;
                c = a[p1] - '0';
            } else {
                r += '1' - c;
                // keep c
            }
            p1 -= 1;
            p2 -= 1;
        }
        
        while (p1 >= 0) {
            if (a[p1] == '0') {
                r += '0' + c;
                c = a[p1] - '0';
            } else {
                r += '1' - c;
                // keep c
            }
            p1 -= 1;
        }
        
        while (p2 >= 0) {
            if (b[p2] == '0') {
                r += '0' + c;
                c = b[p2] - '0';
            } else {
                r += '1' - c;
                // keep c
            }
            p2 -= 1;
        }
        
        if (c) {
            r += '1';
        }
        
        reverse(r.begin(), r.end());
        
        return r;
    }
};
