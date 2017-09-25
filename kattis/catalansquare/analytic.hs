binomial (2*n) n `div` (n + 1)
product [1..(2*n)] `div` (product [1..n] * product [1..(2*n - n)] * (n + 1))
product [1..(2*n)] `div` (product [1..n] * product [1..n] * (n + 1))
product [1..(2*n)] `div` ((product [1..n] ^ 2) * (n + 1))
(product [1..n] * product [(n+1)..(2*n)]) `div` ((product [1..n] ^ 2) * (n + 1))
product [(n+1)..(2*n)] `div` (product [1..n] * (n + 1))
product [(n+2)..(2*n)] `div` product [1..n]

let n = 6 in product [(n+2)..(2*n)] `div` product [1..n]
product [8, 9, 10, 11, 12] `div` product [1, 2, 3, 4, 5, 6]
(product [9, 11] * product [8, 10, 12]) `div` (product [1, 2, 3] * product [4, 5, 6])
(product [9, 11] * 2 ^ 3) `div` product [1, 2, 3]

let n = 7 in product [(n+2)..(2*n)] `div` product [1..n]
product [9, 10, 11, 12, 13, 14] `div` product [1, 2, 3, 4, 5, 6, 7]
(product [9, 11, 13] * product [8, 10, 12, 14]) `div` (product [1, 2, 3] * product [4, 5, 6, 7])
(product [9, 11, 13] * 2 ^ 4) `div` product [1, 2, 3]

let (c, d) = n `divMod` 2 in
(n-c+1) * 2
2*n-2*c+2
2*n-(n-d)+2
2*n-n+d+2
n+d+2

let (c, d) = n `divMod` 2 in
product [(n+2)..(2*n)] `div` product [1..n]
product [(n+2)..(2*n)] `div` (product [1..(n-c)] * product [(n-c+1)..n])
(product [(n-d+3),(n-d+5)..(2*n)] * product [(n+d+2),(n+d+4)..(2*n)]) `div` (product [1..(n-c)] * product [(n-c+1)..n])
(product [(n-d+3),(n-d+5)..(2*n)] * (2 ^ c) * product [(n-c+1)..n]) `div` (product [1..(n-c)] * product [(n-c+1)..n])
(product [(n-d+3),(n-d+5)..(2*n)] * (2 ^ c)) `div` product [1..(n-c)]

let (c, d) = n `divMod` 2 in
product [1..n]
product [1,3..n] * product [2,4..(n-d)]
product [1,3..n] * (2 ^ c) * product [1,2..(n-d) `div` 2]
product [1,3..n] * (2 ^ c) * product [1,2..c]
product [1,3..n] * (2 ^ c) * product [1,2..c]
let (c', d') = c `divMod` 2 in
product [1,3..n] * (2 ^ c) * (product [1,3..c] * (2 ^ c') * product [1,2..c'])
...
(2 ^ sum [c, c', c'', ...]) * product [product [1,3..n], product [1,3..c'], product [1,3..c''], ...]
