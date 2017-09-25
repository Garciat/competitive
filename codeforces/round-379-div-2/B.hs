-- http://codeforces.com/problemset/problem/734/B

{-# LANGUAGE BangPatterns #-}
module Main where

import Data.Maybe
import Control.Applicative

import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

readInts = map (fst . fromJust . BS8.readInt) . BS8.words

getInts = readInts <$> BS.getLine

solve k2 k3 k5 k6 =
    max (256 * n256 + 32 * n32After256) (32 * n32 + 256 * n256After32)
    where
        n32  = minimum [k2, k3]
        n256 = minimum [k2, k5, k6]

        n32After256 = min n32 $ max 0 (k2 - n256)
        n256After32 = min n256 $ max 0 (k2 - n32)

main = do
    [!k2, !k3, !k5, !k6] <- getInts
    print $ solve k2 k3 k5 k6
