// https://leetcode.com/problems/merge-sorted-array/

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if (n == 0) {
            return;
        }
        if (m == 0) {
            nums1 = nums2;
            return;
        }
        
        vector<int> ss(m+n, 0);
        int *out = &ss[0];
        
        int i1 = 0;
        int i2 = 0;
        
        for (int i = 0; i < m + n && i1 < m && i2 < n; ++i) {
            cout << i1 << ' ' << i2 << endl;
            if (nums1[i1] <= nums2[i2]) {
                *out++ = nums1[i1++];
            } else if (nums1[i1] > nums2[i2]) {
                *out++ = nums2[i2++];
            }
        }
        
        for (int i = i1; i < m; ++i) {
            *out++ = nums1[i1++];
        }
        
        for (int i = i2; i < n; ++i) {
            *out++ = nums2[i2++];
        }
        
        nums1 = ss;
    }
};
