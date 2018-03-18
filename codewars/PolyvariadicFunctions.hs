{-# LANGUAGE ConstrainedClassMethods #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE FunctionalDependencies #-}
{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE TypeFamilies #-}

module PolyvariadicFunctions where

class PolyAdd a where
    polyAdd' :: Int -> a

instance PolyAdd Int where
    polyAdd' acc = acc

instance (r ~ Int, PolyAdd a) => PolyAdd (r -> a) where
    polyAdd' acc = \x -> polyAdd' (acc + x)

polyAdd :: PolyAdd a => a
polyAdd = polyAdd' 0


class PolyWords a where
    polyWords' :: [String] -> a

instance PolyWords String where
    polyWords' acc = unwords acc

instance (r ~ String, PolyWords a) => PolyWords (r -> a) where
    polyWords' acc = \x -> polyWords' (acc ++ [x])

polyWords :: PolyWords a => a
polyWords = polyWords' []


class PolyList t a | a -> t where
    polyList' :: [t] -> a

instance PolyList t [t] where
    polyList' acc = acc

instance (PolyList t a) => PolyList t (t -> a) where
    polyList' acc = \x -> polyList' (acc ++ [x])

polyList :: PolyList t a => a
polyList = polyList' []
