// https://leetcode.com/problems/rotate-image/

class Solution {
    
struct Pos { int i, j; };

    public:
void rotate(vector<vector<int>>& m) {
    // for every k-th layer:
    for (int k = 0; k < m.size() / 2; ++k) {
        // it has n*n size:
        int n = m.size() - k * 2;
        // apply our 'spiral' rotating procedure n-1 times:
        for (int s = 0; s < n - 1; ++s) {
            // `s` is our current 'step'

            // top-left corner,  moving right   (j += s)
            Pos p1 { k,             k + s };
            // top-right corner, moving down    (i += s)
            Pos p2 { k + s,         k + n - 1 };
            // bottom-right corner, moving left (j -= s)
            Pos p3 { k + n - 1,     k + n - 1 - s };
            // bototm-left corner,  moving up   (i -= s)
            Pos p4 { k + n - 1 - s, k };
            
            // swap clockwise
            tie(at(m, p1), at(m, p2), at(m, p3), at(m, p4))
                = make_tuple(at(m, p4), at(m, p1), at(m, p2), at(m, p3));
        }
    }
}

int& at(vector<vector<int>>& m, Pos p) {
    return m[p.i][p.j];
}
};

