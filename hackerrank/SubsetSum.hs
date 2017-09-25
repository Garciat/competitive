-- https://www.hackerrank.com/challenges/subset-sum

import Data.Maybe
import Data.List
import Control.Monad
import Control.Applicative

import Data.Vector (Vector, (!))
import qualified Data.Vector as Vector

import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) <$> BS.getLine :: IO [Int]

upperBound :: Vector Int -> Int -> Int -> Int
upperBound ary n x = go 0 n where
    go lb ub
        | lb >= ub = ub
        | ary ! mid < x  = go (mid+1) ub
        | ary ! mid == x = mid
        | ary ! mid > x  = go lb mid
        where mid = (lb + ub) `div` 2

main = do
    _ <- getLine
    xs <- (Vector.scanl (+) 0 . Vector.reverse . Vector.fromList . sort) <$> getInts
    n <- read <$> getLine
    replicateM_ n $ do
        k <- read <$> getLine
        let ans = upperBound xs (Vector.length xs) k
        if ans >= (Vector.length xs)
            then print (-1)
            else print ans
