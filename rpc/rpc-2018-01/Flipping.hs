solve n k = 0.5 ^ k * sum (zipWith (*) [0..] $ iterateN k step initial)
    where
        initial = 1 : replicate n 0

iterateN n f x = iterate f x !! n

step xs = go 0 xs
    where
        go c [x, y] = [c + x + y, x + y]
        go c (x:xs) = (c + x) : go x xs

main = do
    [n, k] <- map read . words <$> getLine
    print (solve n k)
