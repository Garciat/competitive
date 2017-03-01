module Main (main) where

import Control.Monad
import Control.Applicative


type GroupCount = (Int, Int, Int, Int, Int)


countGroups :: [Int] -> GroupCount
countGroups = foldl f (0, 0, 0, 0, 0)
    where
        f (a, b, c, d, e) 1 = (a+1, b, c, d, e)
        f (a, b, c, d, e) 2 = (a, b+1, c, d, e)
        f (a, b, c, d, e) 3 = (a, b, c+1, d, e)
        f (a, b, c, d, e) 4 = (a, b, c, d+1, e)
        f (a, b, c, d, e) 5 = (a, b, c, d, e+1)


solve :: [Int] -> [Int] -> Int
solve as bs = if canSolve then answer else -1
    where
        (a, b, c, d, e) = countGroups as
        (p, q, r, s, t) = countGroups bs

        diffs = [ a - p
                , b - q
                , c - r
                , d - s
                , e - t
                ]
        
        canSolve = all even diffs
        answer = sum (map abs diffs) `quot` 4


main :: IO ()
main = do
    n <- readLn
    as <- readInts n
    bs <- readInts n
    print (solve as bs)


readInts :: Int -> IO [Int]
readInts n = map read . words <$> getLine
