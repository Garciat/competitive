-- https://leetcode.com/problems/count-binary-substrings/

splitByEqualRuns :: Eq a => [a] -> [[a]]
splitByEqualRuns [] = []
splitByEqualRuns (x:xs) =
    let (as, bs) = span (== x) xs
    in (x:as) : splitByEqualRuns bs


pairwiseWith :: (a -> a -> b) -> [a] -> [b]
pairwiseWith f xs = zipWith f xs (tail xs)


countBinarySubstrings :: Eq a => [a] -> Int
countBinarySubstrings =
    sum . pairwiseWith min . map length . splitByEqualRuns
