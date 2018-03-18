{-# LANGUAGE GADTs         #-}
{-# LANGUAGE TypeFamilies  #-}
{-# LANGUAGE TypeOperators #-}

module AdditionCommutes
  ( plusCommutes ) where

import Kata.AdditionCommutes.Definitions
  ( Z, S
  , Natural(..), Equal(..)
  , (:+:))

-- These are some lemmas that may be helpful.
-- They will *not* be tested, so rename them
-- if you so desire. Good luck!

-- | For any n, n = n.
reflexive :: Natural n -> Equal n n
reflexive NumZ     = EqlZ
reflexive (NumS n) = EqlS (reflexive n)

-- | if a = b, then b = a.
symmetric :: Equal a b -> Equal b a
symmetric EqlZ     = EqlZ
symmetric (EqlS n) = EqlS (symmetric n)

-- | if a = b and b = c, then a = c.
transitive :: Equal a b -> Equal b c -> Equal a c
transitive EqlZ EqlZ = EqlZ
transitive (EqlS n) (EqlS m) = EqlS (transitive n m)

identR :: Natural a -> Equal a (a :+: Z)
identR NumZ = EqlZ
identR (NumS n) = EqlS (identR n)

identL :: Natural a -> Equal a (Z :+: a)
identL NumZ = EqlZ
identL (NumS n) = EqlS (identL n)

plus :: Natural a -> Natural b -> Natural (a :+: b)
plus NumZ m = m
plus (NumS n) m = NumS (plus n m)

assoc :: Natural a -> Natural b -> Natural c -> Equal (a :+: (b :+: c)) ((a :+: b) :+: c)
assoc NumZ b c = reflexive (plus b c)
assoc (NumS a) b c = EqlS (assoc a b c)

plusSuccRightSucc :: Natural a -> Natural b -> Equal (S (a :+: b)) (a :+: S b)
plusSuccRightSucc NumZ b = EqlS (reflexive b)
plusSuccRightSucc (NumS a) b = EqlS (plusSuccRightSucc a b)

one :: Natural (S Z)
one = NumS NumZ

-- This is the proof that the kata requires.
-- | a + b = b + a
plusCommutes :: Natural a -> Natural b -> Equal (a :+: b) (b :+: a)
plusCommutes NumZ m =
  transitive (symmetric $ identL m) (identR m)
plusCommutes (NumS n) m =
  transitive (EqlS (plusCommutes n m)) (plusSuccRightSucc m n)