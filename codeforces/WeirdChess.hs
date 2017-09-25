-- http://codeforces.com/problemset/problem/538/D

import Data.Set (Set)
import qualified Data.Set as Set

import Data.List
import Data.Maybe
import Control.Monad

import Data.Array.IArray
import Data.Array.ST
import Control.Monad.ST

type Coord = (Int, Int)

type Cloud = Set Coord

(.+.) :: Coord -> Coord -> Coord
(a, b) .+. (c, d) = (a + c, b + d)

(.-.) :: Coord -> Coord -> Coord
(a, b) .-. (c, d) = (a - c, b - d)

negC :: Coord -> Coord
negC (a, b) = (-a, -b)

translate :: Cloud -> Coord -> Cloud
translate cloud p = Set.map (.+. p) cloud

transforms :: Cloud -> Cloud -> [Cloud]
transforms cloud cs = zipWith translate (repeat cloud) (Set.toList cs)

discarding :: Cloud -> [Cloud] -> Cloud
discarding s ts = s Set.\\ Set.unions ts

solve :: Int -> [[Symb]] -> Maybe [[Symb]]
solve n mx = if good then Just (materialize (2*n - 1) answer) else Nothing
  where
    size  = (n - 1, n - 1)
    pieces  = whereSymb Piece mx
    attacks = whereSymb Attack mx
    empties = whereSymb Empty mx
    antipieces = Set.map (\p -> size .-. p) pieces
    attacks' = antipieces `transforms` attacks
    empties' = antipieces `transforms` empties
    answer = Set.unions attacks' `discarding` empties'
    answerAtOrigin = answer `translate` negC size
    proposal = Set.filter (not . outside) $ Set.unions $ pieces `transforms` answerAtOrigin
    good = (attacks Set.\\ proposal) == Set.empty
    --
    outside (x, y) = x < 0 || y < 0 || x >= n || y >= n

-- http://hackage.haskell.org/package/split-0.2.2/docs/src/Data-List-Split-Internals.html#chunksOf
chunksOf :: Int -> [e] -> [[e]]
chunksOf i ls = map (take i) (build (splitter ls)) where
  splitter :: [e] -> ([e] -> a -> a) -> a -> a
  splitter [] _ n = n
  splitter l c n  = l `c` splitter (drop i l) c n
  build :: ((a -> [a] -> [a]) -> [a] -> [a]) -> [a]
  build g = g (:) []

materialize :: Int -> Cloud -> [[Symb]]
materialize n mx = toList $ runSTUArray $ do
  arr <- newArray (0, n * n - 1) (fromEnum Empty) :: ST s (STUArray s Int Int)
  forM (Set.toList mx) (\(i, j) -> writeArray arr (i*n + j) (fromEnum Attack))
  writeArray arr (n'*n + n') (fromEnum Piece)
  return arr
  where
    n' = n `div` 2
    toList = chunksOf n . map toEnum . elems

data Symb = Empty | Attack | Piece deriving (Eq, Enum)

symb :: Char -> Symb
symb '.' = Empty
symb 'x' = Attack
symb 'o' = Piece
symb x = error ("poop: " ++ show x)

unsymb :: Symb -> Char
unsymb Empty  = '.'
unsymb Attack = 'x'
unsymb Piece  = 'o'

matrix :: (Coord -> a -> b) -> [[a]] -> [[b]]
matrix f xss = [[f (i, j) x | (j, x) <- zip [0..] xs] | (i, xs) <- zip [0..] xss]

whereSymb :: Symb -> [[Symb]] -> Cloud
whereSymb s = Set.fromList . catMaybes . concat . matrix pick
  where
    pick x t = if s == t then Just x else Nothing

input :: IO (Int, [[Symb]])
input = do
  n <- readLn
  lns <- replicateM n getLine
  return (n, parse lns)
  where
    parse = map (map symb)

output :: Maybe [[Symb]] -> IO ()
output mmx =
  case mmx of
    Nothing -> putStrLn "NO"
    Just mx -> do
      putStrLn "YES"
      putStrLn (gen mx)
  where
    gen = concat . map ((++ "\n") . map unsymb)

main = output . uncurry solve =<< input
