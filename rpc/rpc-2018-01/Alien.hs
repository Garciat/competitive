module AlienSunset where

import Control.Monad (replicateM)
import Data.Maybe    (listToMaybe)
import Data.List     (transpose, findIndex)

data Settlement
    = Settlement
    { solarDayLength :: Int
    , sunriseHour    :: Int
    , sunsetHour     :: Int
    }

isNightFor :: Settlement -> Int -> Bool
isNightFor (Settlement _ r t)
    | r < t     = \x -> x <= r || x >= t
    | otherwise = \x -> x <= r && x >= t

makeSolarDayHours :: Settlement -> [Bool]
makeSolarDayHours settlement = cycle (map (isNightFor settlement) hoursOfSolarDay)
    where
        hoursOfSolarDay = take (solarDayLength settlement) [0..]

hoursUntilDarkness :: [Settlement] -> Maybe Int
hoursUntilDarkness settlements = findIndex and hoursByDayUntilPresidentTerm
    where
        longestSolarDay                     = maximum (map solarDayLength settlements)
        presidentTerm                       = 1825 * longestSolarDay
        hoursBySettlement                   = map makeSolarDayHours settlements
        hoursBySettlementUntilPresidentTerm = map (take presidentTerm) hoursBySettlement
        hoursByDayUntilPresidentTerm        = transpose hoursBySettlementUntilPresidentTerm

readLnSpaced :: Read a => IO [a]
readLnSpaced = map read . words <$> getLine

readSettlement :: IO Settlement
readSettlement = do
    [h, r, t] <- readLnSpaced
    pure (Settlement h r t)

readProblemInput :: IO [Settlement]
readProblemInput = do
    n <- readLn
    replicateM n readSettlement

solveProblem :: [Settlement] -> String
solveProblem settlements =
    case hoursUntilDarkness settlements of
        Nothing -> "impossible"
        Just h  -> show h

runCase :: IO ()
runCase = putStrLn =<< solveProblem <$> readProblemInput

main = do
    print (hoursUntilDarkness [Settlement 24 7 19, Settlement 24 18 6])
    print (hoursUntilDarkness [Settlement 10 8 2, Settlement 15 5 10, Settlement 20 15 10])
    print (hoursUntilDarkness [Settlement 6 4 2, Settlement 12 7 5])
    print (hoursUntilDarkness [Settlement 10 5 6, Settlement 10 6 5])
