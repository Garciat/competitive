{-# LANGUAGE ScopedTypeVariables, Rank2Types, TupleSections #-}
module ScottEncoding where

import Prelude hiding (null, length, map, foldl, foldr, take, fst, snd, curry, uncurry, concat, zip, (++))

newtype SMaybe a = SMaybe { runMaybe :: forall b. b -> (a -> b) -> b }
newtype SList a = SList { runList :: forall b. b -> (a -> SList a -> b) -> b }
newtype SEither a b = SEither { runEither :: forall c. (a -> c) -> (b -> c) -> c }
newtype SPair a b = SPair { runPair :: forall c. (a -> b -> c) -> c }

pair :: a -> b -> SPair a b
pair x y = fromPair (x, y)
toPair :: SPair a b -> (a,b)
toPair (SPair f) = f (,)
fromPair :: (a,b) -> SPair a b
fromPair (x, y) = SPair (\f -> f x y)
fst :: SPair a b -> a
fst (SPair f) = f const
snd :: SPair a b -> b
snd (SPair f) = f (flip const)
swap :: SPair a b -> SPair b a
swap p = let (x, y) = toPair p in fromPair (y, x)
curry :: (SPair a b -> c) -> (a -> b -> c)
curry f x y = f (pair x y)
uncurry :: (a -> b -> c) -> (SPair a b -> c)
uncurry f p = f (fst p) (snd p)

toMaybe :: SMaybe a -> Maybe a
toMaybe (SMaybe f) = f Nothing Just
fromMaybe :: Maybe a -> SMaybe a
fromMaybe x = SMaybe (\y f -> maybe y f x)
isJust :: SMaybe a -> Bool
isJust = maybe False (const True) . toMaybe
isNothing :: SMaybe a -> Bool
isNothing = not . isJust
catMaybes :: SList (SMaybe a) -> SList a
catMaybes (SList f) =
  f empty (\(SMaybe g) xs -> g (catMaybes xs) (\x -> cons x (catMaybes xs)))

toEither :: SEither a b -> Either a b
toEither (SEither f) = f Left Right
fromEither :: Either a b -> SEither a b
fromEither x = SEither (\f g -> either f g x)
isLeft :: SEither a b -> Bool
isLeft = either (const True) (const False) . toEither
isRight :: SEither a b -> Bool
isRight = not . isLeft
partition :: SList (SEither a b) -> SPair (SList a) (SList b)
partition =
  foldr (\(SEither f) p ->
          f (\x -> pair (cons x (fst p)) (snd p))
            (\x -> pair (fst p) (cons x (snd p))))
        (pair empty empty)

empty :: SList a
empty = SList (\f g -> f)
cons :: a -> SList a -> SList a
cons x xs = SList (\f g -> g x xs)
toList :: SList a -> [a]
toList (SList f) = f [] (\x xs -> x : toList xs)
fromList :: [a] -> SList a
fromList [] = empty
fromList (x:xs) = cons x (fromList xs)
concat :: SList a -> SList a -> SList a
concat (SList f) ys = f empty (\x xs -> cons x (concat xs ys))
null :: SList a -> Bool
null (SList f) = f True (\_ _ -> False)
length :: SList a -> Int
length (SList f) = f 0 (\x xs -> 1 + length xs)
map :: (a -> b) -> SList a -> SList b
map f (SList a) = a empty (\x xs -> cons (f x) (map f xs))
zip :: SList a -> SList b -> SList (SPair a b)
zip (SList f) (SList g) =
  f empty (\x xs -> g empty (\y ys -> cons (pair x y) (zip xs ys)))
foldl :: (b -> a -> b) -> b -> SList a -> b
foldl f o (SList a) = a o (\x xs -> foldl f (o `f` x) xs)
foldr :: (a -> b -> b) -> b -> SList a -> b
foldr f o (SList a) = a o (\x xs -> x `f` foldr f o xs)
take :: Int -> SList a -> SList a
take 0 _ = empty
take n (SList f) = f empty (\x xs -> cons x (take (n-1) xs))
