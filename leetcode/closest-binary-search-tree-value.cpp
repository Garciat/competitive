// https://leetcode.com/problems/closest-binary-search-tree-value/

class Solution {
public:
  int closestValue(TreeNode* root, double target) {
    return closestValueImpl(root, target, root->val);
  }
  
private:
  int closestValueImpl(TreeNode* root, double target, int bestSoFar) {
    if (!root) return bestSoFar;
    
    if (fabs(target - bestSoFar) > fabs(target - root->val)) {
      bestSoFar = root->val;
    }
    
    if (target <= root->val) {
      return closestValueImpl(root->left, target, bestSoFar);
    }
    return closestValueImpl(root->right, target, bestSoFar);
  }
};
