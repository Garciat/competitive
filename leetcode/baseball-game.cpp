// https://leetcode.com/problems/baseball-game/

int parse_int(const string &s) {
    istringstream iss{s};
    int x;
    iss >> x;
    return x;
}

class Solution {
public:
    int calPoints(vector<string>& ops) {
        vector<int> nums;
        for (const auto& op : ops) {
            if (op == "+") {
                int val = nums[nums.size()-2] + nums[nums.size()-1];
                nums.push_back(val);
            } else if (op == "D") {
                int val = 2 * nums[nums.size()-1];
                nums.push_back(val);
            } else if (op == "C") {
                nums.pop_back();
            } else {
                nums.push_back(parse_int(op));
            }
        }
        int ans = 0;
        for (int x : nums) {
            ans += x;
        }
        return ans;
    }
};
