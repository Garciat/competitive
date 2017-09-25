{-# LANGUAGE BangPatterns #-}

import qualified Data.ByteString.Lazy.Char8 as L

twodivs :: Int -> [Int]
twodivs n = go n []
  where
    go !x xs
      | x == 0     = xs
      | otherwise = go (x `quot` 2) (x : xs)

meowfact :: [Int] -> Integer
meowfact ts = go 1 1 3 (dropWhile (< 3) $ ts)
  where
    go :: Integer -> Integer -> Int -> [Int] -> Integer
    go !r !p !x [] = r
    go !r !p !x (t:ts)
      | x > t     = go (r * p) p x ts
      | otherwise = go r (p * toInteger x) (x+2) (t:ts)

prod :: Int -> Int -> Int -> Integer
prod ox dx mx = go 1 ox
  where
    go :: Integer -> Int -> Integer
    go !p !x
      | x > mx    = p
      | otherwise = go (p * toInteger x) (x + dx)

catalan :: Int -> Integer
catalan n = top `quot` bot
  where
    (c, d) = n `quotRem` 2
    m = n - c
    ts = twodivs m
    g = sum $ init ts
    k = 2 ^ (c - g)
    top = toInteger k * prod (n - d + 3) 2 (2 * n)
    bot = meowfact ts

main = do
  ss <- L.getContents
  let Just (n, _) = L.readInt ss
  print $ catalan (n+1)
