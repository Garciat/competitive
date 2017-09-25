// https://leetcode.com/problems/queue-reconstruction-by-height/

bool my_sorter(pair<int, int> x, pair<int, int> y) {
    if (x.first == y.first) {
        return x.second < y.second;
    }
    return y.first < x.first;
}

class Solution {
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        
        sort(people.begin(), people.end(), my_sorter);
        
        vector<pair<int, int>> ans;
        
        for (int i = 0; i < people.size(); ++i) {
            ans.insert(ans.begin() + people[i].second, people[i]);
        }
        
        return ans;
    }
};
