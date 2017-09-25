// https://leetcode.com/problems/valid-sudoku/


using usable_t = array<bool, 9>;

template <typename Container, typename T>
void fill(Container &&cont, const T &val) {
    fill(begin(cont), end(cont), val);
}

usable_t all_usable() {
    usable_t u;
    fill(u, true);
    return u;
}

template <typename T>
T get_set(T &x, T y) {
    T old = x;
    x = y;
    return old;
}

class Solution {
public:
    
    array<usable_t, 9> blks, rows, cols;
    
    Solution() {
        fill(blks, all_usable());
        fill(rows, all_usable());
        fill(cols, all_usable());
    }
    
    bool do_move(int i, int j, int n) {
        int bi = i / 3;
        int bj = j / 3;
        
        if (!get_set(blks[bi*3+bj][n], false)) {
            return false;
        }
        
        if (!get_set(rows[i][n], false)) {
            return false;
        }
        
        if (!get_set(cols[j][n], false)) {
            return false;
        }
        
        return true;
    }
    
    bool isValidSudoku(vector<vector<char>>& board) {
        
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char c = board[i][j];
                
                if (c == '.') continue;
                
                if (!do_move(i, j, c - '1')) {
                    return false;
                }
            }
        }
        
        return true;
    }
};

