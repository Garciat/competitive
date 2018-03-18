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

class IdleState n a where
  _idle :: Vec n Int -> a

class PushState n a where
  _push :: Vec n Int -> a

instance (PushState n a) => IdleState n (Push -> a) where
  _idle xs = \Push -> _push xs

instance (IdleState (S n) a) => IdleState (S (S n)) (Add -> a) where
  _idle (VCons x (VCons y xs)) = \Add -> _idle (VCons (x + y) xs)

instance (Integral a) => IdleState (S n) (End -> a) where
  _idle (VCons x _) = \End -> fromIntegral x

instance (r ~ Int, IdleState (S n) a) => PushState n (r -> a) where
  _push xs = \x -> _idle (VCons x xs)

begin :: IdleState Z a => a
begin = _idle VNil

push :: Push
push = Push

add :: Add
add = Add

end :: End
end = End

main = do
  print (begin push 1 push 3 end == 3)
