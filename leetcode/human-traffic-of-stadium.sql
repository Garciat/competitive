-- https://leetcode.com/problems/human-traffic-of-stadium/

# Write your MySQL query statement below
select distinct s.*
from stadium s
join
(
select t1.id as x1, t2.id as x2, t3.id as x3
from stadium t1, stadium t2, stadium t3
where
    t1.id = t2.id+1 and t2.id = t3.id+1
and t1.people >= 100 and t2.people >= 100 and t3.people >= 100
    ) k on s.id=x1 or s.id=x2 or s.id=x3
order by id
