-- https://leetcode.com/problems/not-boring-movies/

# Write your MySQL query statement below
select * from cinema where mod(id, 2) = 1 and description not like 'boring' order by rating desc
