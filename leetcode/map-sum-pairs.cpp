// https://leetcode.com/problems/map-sum-pairs/

struct TNode {
    unordered_map<char, TNode*> children;
    int sum;
    
    TNode() {
        sum = 0;
    }
    
    void insert(const string& k, int v, int i = 0) {
        sum += v;
        
        TNode*& child = children[k[i]];
        if (child == nullptr) {
            child = new TNode;
        }
        
        if (i < k.size())
            child->insert(k, v, i+1);
    }
    
    int find_sum(const string& k, int i = 0) {
        if (i == k.size()) {
            return sum;
        } else {
            auto child = children.find(k[i]);
            if (child == children.end()) return 0;
            return child->second->find_sum(k, i+1);
        }
    }
};

class MapSum {
    unordered_map<string, int> current;
    TNode root;
    
public:
    MapSum() {
        
    }
    
    void insert(string key, int val) {
        int v = val - current[key];
        current[key] = val;
        
        root.insert(key, v);
    }
    
    int sum(string prefix) {
        return root.find_sum(prefix);
    }
};
