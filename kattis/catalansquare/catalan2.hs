{-# LANGUAGE BangPatterns #-}

import qualified Data.ByteString.Lazy.Char8 as L

g :: Int -> Int -> Int
g 0 !x = x
g !i !x = let y = i `div` 2 in g y (x + y)

f :: Int -> Integer -> Integer
f 0 !x = x
f 1 !x = x
f !i !x = let y = i `div` 2 in f y (x * prod 1 2 i)

prod :: Int -> Int -> Int -> Integer
prod !x !dx !mx = go x 1
  where
    go :: Int -> Integer -> Integer
    go !x !p
      | x <= mx   = go (x + dx) (p * toInteger x)
      | otherwise = p

catalan :: Int -> Integer
catalan n = top `div` bot
  where
    (!c, !d) = n `quotRem` 2
    !m = n - d
    !k = n - c
    !t = (2 ^ (c - g (n - c) 0)) :: Int
    top = toInteger t * prod (m+3) 2 (2*n)
    bot = f k 1

main = do
  ss <- L.getContents
  let Just (n, _) = L.readInt ss
  print $ catalan (n+1)
