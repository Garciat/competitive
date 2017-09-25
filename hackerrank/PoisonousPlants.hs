-- https://www.hackerrank.com/challenges/poisonous-plants

import Control.Applicative
import Control.Monad

solve :: [Int] -> Int
solve xs = go xs 0
  where
    go xs n =
      let (c, ys) = stage xs in
      if c then n else go ys (n+1)

stage :: [Int] -> (Bool, [Int])
stage xs = go True xs
  where
    go :: Bool -> [Int] -> (Bool, [Int])
    go k (xa:xb:xs) =
      let d = xa >= xb in
      let (c, ys) = go d (xb:xs) in
      (c && d, if k then xa:ys else ys)
    go True xs = (True, xs)
    go False _ = (True, [])

main = do
  getLine
  xs <- map read . words <$> getLine
  let sol = solve xs
  print sol
