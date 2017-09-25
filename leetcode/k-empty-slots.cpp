// https://leetcode.com/problems/k-empty-slots/

class Solution {
public:
    int kEmptySlots(vector<int>& flowers, int k) {
        set<int, less<int>> spotsL;
        set<int, greater<int>> spotsG;
        for (int i = 0; i < flowers.size(); ++i) {
            {
                auto a = spotsG.upper_bound(flowers[i]);
                auto b = spotsG.upper_bound(flowers[i] - k);
                if (a != spotsG.end() && *a == flowers[i] - k - 1 && a == b) {
                    return i + 1;
                }
            }
            {
                auto a = spotsL.upper_bound(flowers[i]);
                auto b = spotsL.upper_bound(flowers[i] + k);
                if (a != spotsL.end() && *a == flowers[i] + k + 1 && a == b) {
                    return i + 1;
                }
            }
            spotsL.insert(flowers[i]);
            spotsG.insert(flowers[i]);
        }
        return -1;
    }
};
