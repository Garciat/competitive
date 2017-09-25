// https://leetcode.com/problems/diagonal-traverse/

/**
 * @param {number[][]} matrix
 * @return {number[]}
 */
var findDiagonalOrder = function(matrix) {
    var ps = [];
    
    for (var i = 0; i < matrix.length; ++i) {
        for (var j = 0; j < matrix[0].length; ++j) {
            ps.push([i+j, i, matrix[i][j]]);
        }
    }
    
    ps.sort(function (a, b) {
        if (a[0] == b[0]) {
            return (a[1] - b[1]) * (a[0] % 2 == 0 ? -1 : 1);
        } else {
            return a[0] - b[0];
        }
    });
    
    return ps.map(function (p) { return p[2]; });
};

