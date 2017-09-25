// https://leetcode.com/problems/validate-ip-address/

class Solution {
public:
    string validIPAddress(string ip) {
        try {
            if (ip.find(':') != string::npos) {
                parseV6(ip);
                return "IPv6";
            } else if (ip.find('.') != string::npos) {
                parseV4(ip);
                return "IPv4";
            } else {
                throw runtime_error{"no kind"};
            }
        }
        catch (runtime_error &e) {
            cout << e.what() << endl;
            return "Neither";
        }
    }
    
    void parseV6(string ip) {
        int p = 0;
        for (int i = 0; i < 8; ++i) {
            int n = 0;
            while (ishex(ip[p])) {
                n += 1;
                if (n > 4)
                    fail(ip, p, "large octet");
                p += 1;
            }
            if (n == 0)
                fail(ip, p, "expected hex");
            if (i == 7)
                break;
            if (ip[p] != ':')
                fail(ip, p, "expected separator");
            p += 1;
        }
        if (p != ip.size())
            fail(ip, p, "extra characters");
    }
    
    void parseV4(string ip) {
        int p = 0;
        for (int i = 0; i < 4; ++i) {
            if (ip[p] == '0' && ip[p+1] && ip[p+1] != '.')
                fail(ip, p, "leading zero");
            int x = 0;
            int n = 0;
            while (isdigit(ip[p])) {
                x *= 10;
                x += ip[p] - '0';
                if (x > 255)
                    fail(ip, p, "large octet");
                n += 1;
                p += 1;
            }
            if (n == 0)
                fail(ip, p, "expected digit");
            if (i == 3)
                break;
            if (ip[p] != '.')
                fail(ip, p, "expected separator");
            p += 1;
        }
        if (p != ip.size())
            fail(ip, p, "extra characters");
    }
    
    static void fail(string ip, int i, string s) {
        string m = to_string(i) + ": " + s + "\n" + ip + "\n" + string(i, ' ') + "^";
        throw runtime_error{m};
    }
    
    static bool ishex(char c) {
        if (c >= '0' && c <= '9')
            return true;
        if (c >= 'a' && c <= 'f')
            return true;
        if (c >= 'A' && c <= 'F')
            return true;
        return false;
    }
};
