-- https://www.hackerrank.com/challenges/brainf-k-interpreter-fp

import Debug.Trace

import Control.Applicative
import Control.Monad

import Data.Word

import Data.Map (Map)
import Data.ByteString (ByteString)

import qualified Data.Map as Map
import qualified Data.ByteString as BS

type Program = ByteString

type DataPtr = Int

type InstrPtr = Int

type Memory = Map Int Word8

type Input = String

type Output = String

type Tick = Int

programSize = BS.length

programInstr prog ip = toEnum $ fromEnum $ BS.index prog ip

programFwd prog ip = go (ip+1) 0
    where
        go ip skips =
            case programInstr prog ip of
                '[' -> go (ip+1) (skips+1)
                ']' -> if skips == 0
                        then ip
                        else go (ip+1) (skips-1)
                otherwise -> go (ip+1) skips

programBwd prog ip = go (ip-1) 0
    where
        go ip skips =
            case programInstr prog ip of
                ']' -> go (ip-1) (skips+1)
                '[' -> if skips == 0
                        then ip
                        else go (ip-1) (skips-1)
                otherwise -> go (ip-1) skips

memoryIncr mem dp = Map.alter (Just . maybe 1 (\x -> x + 1)) dp mem

memoryDecr mem dp = Map.alter (Just . maybe 255 (\x -> x - 1)) dp mem

memoryRead mem dp = toEnum $ fromEnum $ Map.findWithDefault 0 dp mem

memoryWrite mem dp c = Map.insert dp (toEnum $ fromEnum c) mem

run :: Program -> Memory -> InstrPtr -> DataPtr -> Tick -> Input -> Output
run prog mem ip dp tk inp
  | ip == programSize prog = []
  | tk == 100000 = "\nPROCESS TIME OUT. KILLED!!!"
  | otherwise =
        case programInstr prog ip of
            '>' -> run prog mem (ip+1) (dp+1) (tk+1) inp
            '<' -> run prog mem (ip+1) (dp-1) (tk+1) inp
            '+' -> run prog (memoryIncr mem dp) (ip+1) dp (tk+1) inp
            '-' -> run prog (memoryDecr mem dp) (ip+1) dp (tk+1) inp
            '.' -> (memoryRead mem dp) : run prog mem (ip+1) dp (tk+1) inp
            ',' -> run prog (memoryWrite mem dp (head inp)) (ip+1) dp (tk+1) (tail inp)
            '[' -> if memoryRead mem dp == 0
                    then run prog mem (programFwd prog ip) dp (tk+1) inp
                    else run prog mem (ip+1) dp (tk+1) inp
            ']' -> if memoryRead mem dp /= 0
                    then run prog mem (programBwd prog ip) dp (tk+1) inp
                    else run prog mem (ip+1) dp (tk+1) inp

            --'^' -> traceShow mem $ run prog mem (ip+1) dp tk inp
            otherwise -> run prog mem (ip+1) dp tk inp

main = do
    _ <- getLine
    inp <- init <$> getLine
    prog <- BS.getContents
    let out = run prog (Map.empty) 0 0 0 inp
    putStr out
