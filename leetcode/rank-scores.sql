-- https://leetcode.com/problems/rank-scores/

# Write your MySQL query statement below
SELECT
  Score, @rank := @rank + (@prev <> (@prev := Score)) Rank
FROM
  Scores, (SELECT @rank := 0, @prev := -1) init
order BY Score desc
