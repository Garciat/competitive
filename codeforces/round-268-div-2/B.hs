-- http://codeforces.com/problemset/problem/469/B

import Control.Monad (liftM, forM)
import Data.Array (listArray, (!))

for = flip map

trues = repeat True
falses = repeat False

input = do
  ln <- getLine
  return $ map read $ words ln

mor :: [[Bool]] -> [Bool]
mor = foldl1 $ zipWith (||)

main = do
  [p, q, l, r] <- input
  let g n = liftM mor $ forM [1..n] $ \_ -> do
      [a, b] <- input
      return $ (take a falses ++ take (b-a+1) trues ++ take (1001-b) falses)
  ipx <- g p
  iqx <- g q
  let ip = listArray (0, 1001) ipx
  let iq = listArray (0, 1001) iqx
  let li = for [l..r] (\i -> fromEnum $ or $ for [0..1001-i-1] (\j -> ip ! (i+j) && iq ! j))
  putStrLn $ show $ sum li
