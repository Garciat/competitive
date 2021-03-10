module Sudoku where

import Data.List (sortOn, (\\), intersect)

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

rowRange :: [Int]
rowRange = [0..8]

colRange :: [Int]
colRange = [0..8]

cellValues :: [Int]
cellValues = [1..9]

ixRange :: [Ix]
ixRange = [(i, j) | i <- rowRange, j <- colRange]

readBoard :: Board -> Ix -> Int
readBoard b (i, j) = b !! i !! j

emptyIndices :: Board -> [Ix]
emptyIndices b = [ix | ix <- ixRange, readBoard b ix == 0]

cellRow :: Board -> Ix -> Row
cellRow b (i, _) = [readBoard b (i, j) | j <- colRange]

cellCol :: Board -> Ix -> Col
cellCol b (_, j) = [readBoard b (i, j) | i <- rowRange]

cellSquare :: Board -> Ix -> Square
cellSquare b (i, j) = do
  let size = 3
  let x = (i `div` size) * size
  let y = (j `div` size) * size
  i' <- [x..x+size-1]
  j' <- [y..y+size-1]
  return (readBoard b (i', j'))

rowCandidates :: Board -> Ix -> [Int]
rowCandidates b ix = cellValues \\ cellRow b ix

colCandidates :: Board -> Ix -> [Int]
colCandidates b ix = cellValues \\ cellCol b ix

squareCandidates :: Board -> Ix -> [Int]
squareCandidates b ix = cellValues \\ cellSquare b ix

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
