{-# LANGUAGE LambdaCase #-}

module Coroutine where

import Control.Monad (ap, forever, mapM_, when)
import Preloaded

apply :: Coroutine r u d a -> (Command r u d a -> r) -> r
apply = runCoroutine

instance Applicative (Coroutine r u d) where
  pure = return
  (<*>) = ap

instance Monad (Coroutine r u d) where
  return x = Coroutine (\k -> k (Done x))
  
  f >>= g =
    Coroutine $
      \k ->
        apply f $
          \case
            Done a ->
              apply (g a) k
            Out d f' ->
              k (Out d (f' >>= g))
            In u_f' ->
              k (In (\u -> u_f' u >>= g))

(>>>) :: Coroutine r u m a -> Coroutine r m d a -> Coroutine r u d a
p1 >>> p2 =
  Coroutine $
    \k ->
      apply p2 $
        \case
          Done a ->
            k (Done a)
          Out d p2' ->
            k (Out d (p1 >>> p2'))
          In m_p2' ->
            apply p1 $
              \case
                Done a ->
                  k (Done a)
                Out m p1' ->
                  apply (p1' >>> m_p2' m) k
                In u_p1' ->
                  -- ugly: re-runs p2
                  k (In (\u -> u_p1' u >>> p2))

-- It might be useful to define the following function
-- pipe2 :: Coroutine r u m a -> (m -> Coroutine r m d a) -> Coroutine r u d a
-- pipe2 p1 g =
--   Coroutine $
--     \k ->
--       apply p1 $
--         \case
--           Done a ->
--             k (Done a)
--           In u_p1' ->
--             k (In (\u -> pipe2 (u_p1' u) g))
--           Out m p1' ->
--             apply (g m) $
--               \case
--                 Done a ->
--                   k (Done a)
--                 Out d p2' ->
                  

-- Library functions

output :: a -> Coroutine r u a ()
output v =
  Coroutine $
    \k ->
      k (Out v (return ()))

input :: Coroutine r v d v
input =
  Coroutine $
    \k ->
      k (In (\v -> return v))

produce :: [a] -> Coroutine r u a ()
produce xs = mapM_ output xs

consume :: Coroutine [t] u t a -> [t]
consume c =
  apply c $
    \case
      Done a ->
        []
      Out x c' ->
        x : consume c'
      otherwise ->
        error "consume: input expected"

filterC :: (v -> Bool) -> Coroutine r v v ()
filterC p = do
  x <- input
  when (p x) (output x)
  filterC p

limit :: Int -> Coroutine r v v ()
limit 0 = return ()
limit n
  | n < 0     = limit 0
  | otherwise = (input >>= output) *> limit (n-1)

suppress :: Int -> Coroutine r v v ()
suppress 0 = forever (input >>= output)
suppress n
  | n < 0     = suppress 0
  | otherwise = input *> suppress (n-1)

add :: Coroutine r Int Int ()
add = do
  x <- input
  y <- input
  output (x + y)
  add

transform :: (a -> a) -> Coroutine r a a ()
transform f = do
  x <- input
  output (f x)
  transform f

duplicate :: Coroutine r v v ()
duplicate = do
  x <- input
  output x
  output x
  duplicate

-- Programs
-- 1. A program which outputs the first 5 even numbers of a stream.
-- 2. A program which produces a stream of the triangle numbers 
-- 3. A program which multiplies a stream by 2
-- 4. A program which sums adjacent pairs of integers

p1, p2, p3, p4 :: Coroutine r Int Int ()

p1 = filterC even >>> limit 5
p2 = produce [1..] >>> transform triangle
p3 = transform (*2)
p4 = input >>= go
  where
    go x = do
      y <- input
      output (x + y)
      go y

triangle n = (n * (n + 1)) `div` 2
