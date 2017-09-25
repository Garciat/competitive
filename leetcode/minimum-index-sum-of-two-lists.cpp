// https://leetcode.com/problems/minimum-index-sum-of-two-lists/

class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        unordered_map<string, int> m;
        vector<string> ans;
        int k = INT_MAX;
        for (int i = 0; i < list1.size(); ++i) {
            m.insert(make_pair(list1[i], i));
        }
        for (int i = 0; i < list2.size(); ++i) {
            auto it = m.find(list2[i]);
            if (it != m.end()) {
                auto j = it->second;
                if (i + j <= k) {
                    if (i + j < k) {
                        ans.clear();
                        k = i + j;
                    }
                    ans.push_back(list2[i]);
                }
            }
        }
        return ans;
    }
};
