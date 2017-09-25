{-# LANGUAGE BangPatterns #-}
module Danik where

import Control.Applicative

data Result = Anton
            | Danik
            | Friendship
            deriving Show

solve :: String -> Result
solve input = go input 0 0
    where
        go [] !a !d
            | a > d = Anton
            | a < d = Danik
            | otherwise = Friendship
        
        go ('A':cs) !a !d = go cs (a+1) d
        go ('D':cs) !a !d = go cs a (d+1)

main :: IO ()
main = do
    _ <- getLine
    putStrLn =<< (show . solve) <$> getLine
