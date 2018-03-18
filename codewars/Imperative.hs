{-# LANGUAGE GeneralizedNewtypeDeriving #-}

module Imperative (
  def, var, lit, while, (+=), (-=), (*=)
) where

import Control.Monad.State.Strict
import Data.Map.Strict (Map, (!))
import qualified Data.Map.Strict as Map
import Debug.Trace
import Test.Hspec
import Test.QuickCheck

newtype Name = Name String deriving (Eq, Ord, Show)
type Ctx  = Map Name Integer
newtype Imp a =
  Imp { unImp :: (State Ctx a) }
  deriving (Functor, Applicative, Monad, MonadState Ctx)

class ImpValue a where
  valueOf :: a -> Imp Integer

instance ImpValue Integer where
  valueOf = pure

instance ImpValue Name where
  valueOf name = gets (!name)

instance ImpValue a => ImpValue (Imp a) where
  valueOf x = x >>= valueOf

varCounter :: Name
varCounter = Name "__var_count__"

initState :: Ctx
initState = Map.singleton varCounter 0

def :: ImpValue a => Imp a -> Integer
def r = evalState (unImp $ valueOf r) initState

var :: Integer -> Imp Name
var v = do
  i <- gets (!varCounter)
  modify (Map.adjust (+1) varCounter)
  let name = Name ("var" ++ show i)
  name .= lit v
  return name

lit :: Integer -> Integer
lit x = x

while :: Name -> (Integer -> Bool) -> Imp () -> Imp ()
while r f act = do
  continue <- f <$> valueOf r
  if continue
    then act *> while r f act
    else pure ()

(.=) :: ImpValue a => Name -> a -> Imp ()
r .= v = do
  x <- valueOf v
  modify (Map.insert r x)

op :: ImpValue a => (Integer -> Integer -> Integer) -> Name -> a -> Imp ()
op f r v = r .= (f <$> valueOf r <*> valueOf v)

(+=), (-=), (*=) :: ImpValue a => Name -> a -> Imp ()
(+=) = op (+)
(-=) = op (-)
(*=) = op (*)


main = hspec $ do
  describe "what" $ do
    it "something" $ do
      property $ \x -> (def $ return (lit x)) `shouldBe` x
  describe "factorial" $ do
    it "should return the same as the functional one" $ do
      property $ \x -> factorial x `shouldBe` foldr (*) 1 [1..x]
  describe "howManyBetween" $ do
    it "should return the same as the functional one" $ do
      property $ \from to ->
        howManyBetween from to `shouldBe` (max 0 $ to - from - 1 :: Integer)

-- foldr (*) 1
factorial :: Integer -> Integer
factorial n = def $ do
  result <- var 1
  i      <- var n
  while i (>0) $ do
    result *= i
    i      -= lit 1
  return result
  
-- ((max 0 . subtract 1) .) . subtract
howManyBetween :: Integer -> Integer -> Integer
howManyBetween c n = def $ do
  result <- var 0
  i      <- var (c + 1)
  while i (<n) $ do
    result += lit 1
    i      += lit 1
  return result