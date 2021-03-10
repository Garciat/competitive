module Sudoku where

import Data.List (sortOn, (\\), intersect)
import Control.Monad (guard)

---

modifyAt :: Int -> (a -> a) -> [a] -> [a]
modifyAt i f ls
  | i < 0 = ls
  | otherwise = go i ls
  where
    go 0 (x:xs) = f x : xs
    go n (x:xs) = x : go (n-1) xs
    go _ []     = []

---

type Board = [[Int]] -- 9x9
type Row = [Int] -- 9
type Col = [Int] -- 9
type Square = [Int] -- 3x3
type Ix = (Int, Int) -- [0..8] both ; row, col

indices :: [Ix]
indices = do
  i <- [0..8]
  j <- [0..8]
  return (i, j)

readBoard :: Board -> Ix -> Int
readBoard b (i, j) = b !! i !! j

emptyIndices :: Board -> [Ix]
emptyIndices b = [ix | ix <- indices, readBoard b ix == 0]

cellRow :: Board -> Ix -> Row
cellRow b (i, _) = [readBoard b (i, j) | j <- [0..8]]

cellCol :: Board -> Ix -> Col
cellCol b (_, j) = [readBoard b (i, j) | i <- [0..8]]

cellSquare :: Board -> Ix -> Square
cellSquare b (i, j) = do
  let x = (i `div` 3) * 3
  let y = (j `div` 3) * 3
  i' <- [x..x+2]
  j' <- [y..y+2]
  return (readBoard b (i', j'))

rowCandidates :: Board -> Ix -> [Int]
rowCandidates b ix = [1..9] \\ cellRow b ix

colCandidates :: Board -> Ix -> [Int]
colCandidates b ix = [1..9] \\ cellCol b ix

squareCandidates :: Board -> Ix -> [Int]
squareCandidates b ix = [1..9] \\ cellSquare b ix

boardCandidates :: Board -> [(Ix, [Int])]
boardCandidates b = do
  ix <- emptyIndices b
  let row = rowCandidates b ix
  let col = colCandidates b ix
  let sq  = squareCandidates b ix
  return (ix, row `intersect` col `intersect` sq)

makeMove :: Ix -> Int -> Board -> Board
makeMove (i, j) n = modifyAt i (modifyAt j (\_ -> n))

solve :: Board -> [Board]
solve b = do
  -- ranked candidates
  let cands = sortOn (length . snd) (boardCandidates b)
  case cands of
    []         -> return b
    otherwise  -> do
      let (ix, ns) = head cands
      n <- ns
      solve (makeMove ix n b)

sudoku :: Board -> Board
sudoku b = solve b !! 0
