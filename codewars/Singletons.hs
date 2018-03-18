{-# LANGUAGE DataKinds #-}
{-# LANGUAGE DeriveFunctor #-}
{-# LANGUAGE GADTs #-}
{-# LANGUAGE NoImplicitPrelude #-}
{-# LANGUAGE RankNTypes #-}
{-# LANGUAGE TypeFamilies #-}
{-# LANGUAGE TypeOperators #-}

module Singletons where

import Prelude hiding (drop, take, head, tail, index, zipWith, replicate, map, (++))

data Vec a n where
  VNil :: Vec a Zero
  VCons :: a -> Vec a n -> Vec a (Succ n)

data Nat = Zero | Succ Nat

data SNat a where
  SZero :: SNat Zero
  SSucc :: SNat a -> SNat (Succ a)

type family (a :: Nat) :< (b :: Nat) :: Bool
type instance m :< Zero = False
type instance Zero :< Succ n = True
type instance (Succ m) :< (Succ n) = m :< n

type family (Add (a :: Nat) (b :: Nat)) :: Nat
type instance Add Zero m = m
type instance Add (Succ n) m = Succ (Add n m)

type family (Min (a :: Nat) (b :: Nat)) :: Nat
type instance Min n Zero = Zero
type instance Min Zero m = Zero
type instance Min (Succ n) (Succ m) = Succ (Min n m)

type family (Sub (a :: Nat) (b :: Nat)) :: Nat
type instance Sub n Zero = n
type instance Sub Zero m = Zero
type instance Sub (Succ n) (Succ m) = Sub n m

map :: (a -> b) -> Vec a n -> Vec b n
map f VNil = VNil
map f (VCons x xs) = VCons (f x) (map f xs)

index :: ((a :< b) ~ True) => SNat a -> Vec s b -> s
index SZero (VCons x _) = x
index (SSucc n) (VCons _ xs) = index n xs

replicate :: a -> SNat n -> Vec a n
replicate _ SZero = VNil
replicate x (SSucc n) = VCons x (replicate x n)

-- Both vectors must be of equal length
zipWith :: (a -> b -> c) -> Vec a n -> Vec b n -> Vec c n
zipWith f VNil VNil = VNil
zipWith f (VCons x xs) (VCons y ys) = VCons (f x y) (zipWith f xs ys)

(++) :: Vec a m -> Vec a n -> Vec a (Add m n)
VNil ++ ys = ys
(VCons x xs) ++ ys = VCons x (xs ++ ys)

-- The semantics should match that of take for normal lists.
take :: SNat n -> Vec a m -> Vec a (Min n m)
take SZero _ = VNil
take _ VNil  = VNil
take (SSucc n) (VCons x xs) = VCons x (take n xs)

-- The semantics should match that of drop for normal lists.
drop :: SNat n -> Vec a m -> Vec a (Sub m n)
drop SZero xs = xs
drop _ VNil   = VNil
drop (SSucc n) (VCons _ xs) = drop n xs

head :: Vec a (Succ n) -> a
head (VCons x _) = x

tail :: Vec a (Succ n) -> Vec a n
tail (VCons _ xs) = xs