import Data.Function (on)
import Data.List     (minimumBy)

main = do
    n  <- readLn :: IO Int
    hs <- map read . words <$> getLine
    t  <- readLn :: IO Int
    print (minimumBy (compare `on` (t `mod`)) hs)
