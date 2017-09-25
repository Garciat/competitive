catalan :: Integer -> Integer
catalan n = product [n+2..n*2] `div` product [1..n]

main = readLn >>= print . catalan . (+1)