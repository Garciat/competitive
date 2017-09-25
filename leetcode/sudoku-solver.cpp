// https://leetcode.com/problems/sudoku-solver/

struct Move {
  int i, j;
  int n;
};

ostream& operator<<(ostream &os, Move m) {
  return os << '(' << m.i << ',' << m.j << ") = " << m.n;
}

struct Board {
  array<int, 9*9> m;
  
  Board() {
    for (int& x : m) x = -1;
  }
  
  Board(const Board &b) : m(b.m) { }

  bool complete() const {
    for (int x : m)
      if (x == -1)
        return false;
    return true;
  }
  
  int& at(int i, int j) {
    return m[i*9+j];
  }
  
  const int& at(int i, int j) const {
    return m[i*9+j];
  }
  
  void apply(Move m) {
    at(m.i, m.j) = m.n;
  }
  
  bool empty(int i, int j) const {
    return at(i, j) == -1;
  }
  
  vector<Move> movesFor(int i, int j) const {
    vector<Move> r;
    
    array<bool, 9> usable;
    for (bool& b : usable) b = true;
    
    // Square moves
    int si = i / 3 * 3;
    int sj = j / 3 * 3;
    
    for (int m = si; m < si+3; ++m) {
      for (int n = sj; n < sj+3; ++n) {
        if (!empty(m, n))
          usable[at(m, n)] = false;
      }
    }
    
    // Horizontal moves
    for (int k = 0; k < 9; ++k) {
      if (!empty(i, k))
        usable[at(i, k)] = false;
    }
    
    // Vertical moves
    for (int k = 0; k < 9; ++k) {
      if (!empty(k, j))
        usable[at(k, j)] = false;
    }
    
    // Round-up usables
    for (int k = 0; k < 9; ++k) {
      if (usable[k]) {
        r.push_back(Move{i, j, k});
      }
    }
    
    return r;
  }
  
  vector<Move> nextMoves() const {
    vector<Move> r;
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (empty(i, j)) {
          auto t = movesFor(i, j);
          if (!t.size()) {
            return t;
          }
          if (t.size() == 1) {
            return t;
          }
          if (!r.size() || t.size() < r.size()) {
            r = t;
          }
        }
      }
    }
    return r;
  }
};

ostream& operator<<(ostream &os, const Board &b) {
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      int x = b.at(i, j);
      if (x != -1)
        os << (x + 1);
      else
        os << ' ';
    }
    os << '\n';
  }
  return os;
}

bool solve(const Board &b, Board &ans) {
  if (b.complete()) {
    ans = b;
    return true;
  }
  auto ms = b.nextMoves();
  if (!ms.size()) {
    return false;
  }
  for (auto m : ms) {
    Board c = b;
    c.apply(m);
    if (solve(c, ans)) {
      return true;
    }
  }
  return false;
}

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        Board b;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char c = board[i][j];
                if (c == '.') continue;
                b.at(i, j) = c - '1';
            }
        }
        
        Board ans;
        
        if (solve(b, ans)) {
            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    board[i][j] = ans.at(i, j) + '1';
                }
            }
        }
    }
};
