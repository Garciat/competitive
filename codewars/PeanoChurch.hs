{-# LANGUAGE 
  FlexibleInstances, 
  UndecidableInstances, 
  InstanceSigs,
  ScopedTypeVariables,
  RankNTypes #-}

module PeanoChurch where

import Data.List
import Test.Hspec
import Test.QuickCheck
import System.Timeout
import Data.Proxy

type ISO a b = (a -> b, b -> a)
-- See https://www.codewars.com/kata/isomorphism

symm :: ISO a b -> ISO b a
symm (ab, ba) = (ba, ab)

substL :: ISO a b -> (a -> b)
substL = fst

substR :: ISO a b -> (b -> a)
substR = snd

liftISO2 :: ISO a b -> ISO (a -> a -> a) (b -> b -> b)
liftISO2 (ab, ba) =
  ( \f -> \b1 b2 -> ab (f (ba b1) (ba b2))
  , \g -> \a1 a2 -> ba (g (ab a1) (ab a2))
  )

-- A Natural Number is either Zero,
-- or a Successor (1 +) of Natural Number.
-- We have (+)/(*) on Natural Number, or (-) it.
-- Since Natrual Number do not have negative, forall x, 0 - x = 0.
-- We also have pow on Natrual Number
-- Since Haskell is lazy, we also have infinity

class Nat n where
  zero, one :: n
  one = successor zero
  successor :: n -> n
  nat :: a -> (n -> a) -> n -> a -- Pattern Matching
  iter :: a -> (a -> a) -> n -> a -- Induction
  plus, minus, mult, pow :: n -> n -> n
  inf :: n
  inf = successor inf
  divide :: n -> n -> n
  l `divide` r | l == 0 && r == 0 = undefined
  l `divide` r | l < r = 0
  l `divide` r | otherwise = successor $ (l `minus` r) `divide` r
  -- notice (l `divide` 0) when l is not 0 will return inf
  isoP :: ISO n Peano -- See below for the definition of Peano
  isoP = (iter zero successor, iter zero successor)
  toP :: n -> Peano
  toP = substL isoP

instance {-# OVERLAPPABLE #-} Nat n => Show n where
  show = show . toP

instance {-# OVERLAPPABLE #-} Nat n => Eq n where
  l == r = toP l == toP r

instance {-# OVERLAPPABLE #-} Nat n => Ord n where
  l `compare` r = toP l `compare` toP r

instance {-# OVERLAPPABLE #-} Nat n => Num n where
  abs = id
  signum = nat zero (const 1)
  fromInteger 0 = zero
  fromInteger n | n > 0 = successor $ fromInteger (n - 1)
  (+) = plus
  (*) = mult
  (-) = minus


data Peano = O | S Peano deriving (Show, Eq, Ord)

instance Nat Peano where
  zero = O
  successor = S
  
  nat z _ O     = z
  nat _ s (S n) = s n
  
  iter z _ O     = z
  iter z f (S n) = f (iter z f n)
  
  plus n m = iter m successor n
  
  minus O m = O
  minus n O = n
  minus (S n) (S m) = minus n m
  
  mult n m = iter zero (plus m) n
  
  pow n m = iter one (mult n) m


instance Nat [()] where
  zero = []
  successor = (():)
  
  nat z _ [] = z
  nat _ s (():n) = s n
  
  iter z f n = foldr (\() x -> f x) z n
  
  plus = (++)
  minus = (\\)
  mult = (*>)
  pow n m = iter one (mult n) m

-- Instead of defining Nat from zero, sucessor (and get Peano),
-- We can define it from Pattern Matching
newtype Scott = Scott { runScott :: forall a. a -> (Scott -> a) -> a }
instance Nat Scott where
  zero = Scott (\z s -> z)
  successor n = Scott (\z s -> s n)
  
  nat z s n = runScott n z s
  
  iter z f n = runScott n z (\n' -> f (iter z f n'))
  
  plus = substR (liftISO2 isoP) plus
  minus = substR (liftISO2 isoP) minus
  mult = substR (liftISO2 isoP) mult
  pow = substR (liftISO2 isoP) pow

-- Or from induction!
newtype Church = Church { runChurch :: forall a. (a -> a) -> a -> a }

predecessor :: Church -> Church
predecessor n =
  Church (\f x ->
    let (p, _) = runChurch n (\(_, g) -> (g, f . g)) (id, id)
      in p x)

instance Nat Church where
  zero = Church (\f x -> x)
  successor n = Church (\f x -> f (runChurch n f x))
  
  nat z s n = runChurch n (\_ -> s (predecessor n)) z
  
  iter z s n = runChurch n s z
  
  plus n m = Church (\f x -> runChurch n f (runChurch m f x))
  
  minus n m = runChurch m predecessor n
  
  mult n m = Church (\f -> runChurch n (runChurch m f))
  
  pow n m = Church (runChurch m (runChurch n))


test :: (Nat n, Num n, Eq n, Show n) => Proxy n -> Spec
test (p :: Proxy n) = do
  it "0 + x = x" $
    property (\(NonNegative x) -> 0 + from x == from x)
  it "successor x + y = successor (x + y)" $
    property (\(NonNegative x) (NonNegative y) ->
      successor (from x) + from y == successor (from x + from y))
  it "0 * x = 0" $
    property (\(NonNegative x) -> 0 * from x == 0)
  it "0 - x = 0" $
    property (\(NonNegative x) -> 0 - from x == 0)
  it "x - 0 = x" $
    property (\(NonNegative x) -> from x - 0 == from x)
  it "successor x - successor y = x - y" $
    property (\(NonNegative x) (NonNegative y) ->
      successor (from x) - successor (from y) == from x - from y)
  it "successor x * y = y + (x * y)" $
    property (\(NonNegative x) (NonNegative y) -> 
      successor (from x) * from y == from y + from x * from y)
  it "x `pow` 0 == 1" $
    property (\(NonNegative x) -> from x `pow` 0 == 1)
  it "2 ^ 3 == 8" $
    2 `pow` 3 `shouldBe` from 8
  it "3 ^ 2 == 9" $
    3 `pow` 2 `shouldBe` from 9
  it "pred 0 == Nothing" $
    pred (from 0) `shouldBe` Nothing
  it "pred (successor x) == Just x" $
    property (\(NonNegative x) -> 
      pred (successor (from x)) == Just (from x))
  it "iter 0 (1 +) x == x" $
    property (\(NonNegative x) -> iter 0 (1 +) (from x) == x)
  where
    from x = fromInteger x :: n
    pred = nat Nothing Just


main = do
  hspec $ describe "Peano" $ test (Proxy :: Proxy Peano)
  hspec $ describe "[()]" $ test (Proxy :: Proxy [()])
  hspec $ describe "Scott" $ test (Proxy :: Proxy Scott)
  hspec $ describe "Church" $ test (Proxy :: Proxy Church)