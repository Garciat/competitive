-- http://codeforces.com/problemset/problem/913/C

import Control.Applicative ((<$>))

data Offer = Offer { volume :: Integer
                   , cost :: Integer
                   } deriving (Show, Eq, Ord)

doubleOffer :: Offer -> Offer
doubleOffer (Offer v c) = Offer (2 * v) (2 * c)

mapWithPrev :: (a -> a -> a) -> [a] -> [a]
mapWithPrev f = go
  where
    go (x:x':xs) = x : go (f x x' : xs)
    go xs = xs

-- reverses the offer list
optimizeOffers :: Integer -> [Offer] -> [Offer]
optimizeOffers v = fillExtra . mapWithPrev optBwd . reverse . mapWithPrev optFwd
  where
    optFwd prev curr = min (doubleOffer prev) curr

    optBwd prev curr = curr {cost=min (cost prev) (cost curr)}

    fillExtra (x:xs)
      | volume x > v = (x:xs)
      | otherwise    = fillExtra (doubleOffer x : x : xs)

optimizeCost :: Integer -> [Offer] -> Integer
optimizeCost left (Offer v c:xs)
  | left <= 0 = 0
  | null xs   = c
  | v <= left = c + optimizeCost (left - v) xs
  | otherwise = min c (optimizeCost left xs)

solve :: Integer -> [Offer] -> Integer
solve v xs = optimizeCost v (optimizeOffers v xs)

readIntegers :: IO [Integer]
readIntegers = fmap read . words <$> getLine

powersOf2 :: [Integer]
powersOf2 = map (2^) [0..]

readOffers :: IO [Offer]
readOffers = zipWith Offer powersOf2 <$> readIntegers

main = do
  [_, v] <- readIntegers
  offers <- readOffers
  print (solve v offers)
