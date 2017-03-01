module Main (main) where

import Control.Monad
import Control.Applicative


solve :: Int -> Int -> Int
solve 0 _ = 0
solve n k = go n k 0 0
    where
        go _ 0 _ c = c
        go 0 _ d _ = d - 1
        go n k d c =
            let (q, r) = n `quotRem` 10 in
                if r == 0 then go q (k-1) (d+1) c
                          else go q k (d+1) (c+1)


main :: IO ()
main = do
    [n, k] <- map read . words <$> getLine
    print (solve n k)
