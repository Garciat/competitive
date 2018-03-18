{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE GADTs #-}
{-# LANGUAGE KindSignatures #-}
{-# LANGUAGE MultiParamTypeClasses #-}

module Postfix where

data Z
data S n

data Push = Push
data Add  = Add
data End  = End

data Vec n a where
  VNil  :: Vec Z a
  VCons :: a -> Vec n a -> Vec (S n) a

class Prog n a where
  _prog :: Vec n Int -> a

instance (r ~ Int, Prog (S n) a) => Prog n (Push -> r -> a) where
  _prog xs = \Push x -> _prog (VCons x xs)

instance (Prog (S n) a) => Prog (S (S n)) (Add -> a) where
  _prog (VCons x (VCons y xs)) = \Add -> _prog (VCons (x + y) xs)

instance (Integral a) => Prog (S n) (End -> a) where
  _prog (VCons x _) = \End -> fromIntegral x

begin :: Prog Z a => a
begin = _prog VNil

push :: Push
push = Push

add :: Add
add = Add

end :: End
end = End
