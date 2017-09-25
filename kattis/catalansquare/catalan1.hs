catalan :: Integer -> Integer
catalan n = ((2^c) * product [m+3,m+5..n*2]) `div` product [1..(n-c)]
  where
    (c, d) = n `quotRem` 2
    m = n - d

main = readLn >>= print . catalan . (+1)