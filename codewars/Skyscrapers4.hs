{-# LANGUAGE BangPatterns #-}
{-# LANGUAGE FlexibleContexts #-}

module Skyscrapers4 where

import Control.Monad
import Data.List           (groupBy, intercalate, permutations, transpose)
import Data.Map.Strict     (Map)
import Data.Vector.Unboxed (Vector)

import qualified Data.Map.Strict     as M
import qualified Data.Vector.Unboxed as V

import Debug.Trace

type Strip = Vector Int
type Clues = [[Int]]
type Puzzle = [[Int]]

allStrips :: Int -> [Strip]
allStrips n = V.fromList <$> permutations [1..n]

stripRank :: Strip -> Int
stripRank xs = snd $ V.foldl' (\(m, r) x -> (max m x, if x >= m then r+1 else r)) (V.head xs, 0) xs

rankedStrips :: Int -> Map Int [Strip]
rankedStrips n = M.fromList $ (0, strips):[(r, stripsOf r) | r <- [1..n]]
  where
    strips = allStrips n
    ranked = [(stripRank s, s) | s <- strips]
    stripsOf rank = map snd $ filter ((== rank) . fst) ranked

solution :: Int -> [Int] -> [Strip]
solution n clues = go 0 initial
  where
    strips  = rankedStrips n
    initial = (strips M.!) <$> clues

    go :: Int -> [[Strip]] -> [Strip]
    go i options
      | i == length clues = take n $ map head options
      | otherwise = do
        strip <- options !! i
        case constrain n i strip options of
          Just options' -> go (i+1) options'
          otherwise     -> []

constrain :: Int -> Int -> Strip -> [[Strip]] -> Maybe [[Strip]]
constrain n i strip =
  zipWithM g [0..]
  where
    (!a, !c) = i `divMod` n

    g j level =
      case f j level of
        [] -> Nothing
        xs -> Just xs

    f :: Int -> [Strip] -> [Strip]
    f j level
      -- me
      | i == j = [strip]
      -- exact opposite
      | abs (a-b) == 2 && abs (c-d) == n-1 = filter (\s -> V.reverse strip == s) level
      -- to the right
      | (a+1) `mod` 4 == b = filter (\s -> strip V.! d == s V.! (n-c-1)) level
      -- to the left
      | (a-1) `mod` 4 == b = filter (\s -> strip V.! (n-d-1) == s V.! c) level
      | otherwise = level
      where
        (!b, !d) = j `divMod` n

formatSolution :: Int -> [Strip] -> String
formatSolution n strips = intercalate "\n" $ map row [0..n-1]
  where
    row i    = intercalate " " $ map (cell i) [0..n-1]
    cell i j = show $ (strips !! j) V.! i


solve :: Clues -> Puzzle
solve = f . concat
  where
    f clues = transpose $ V.toList <$> solution (length clues `div` 4) clues
