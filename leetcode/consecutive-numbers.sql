-- https://leetcode.com/problems/consecutive-numbers/

# Write your MySQL query statement below
select distinct t1.Num as ConsecutiveNums
from Logs t1
join Logs t2 on t1.id+1=t2.id
join Logs t3 on t2.id+1=t3.id
where t1.Num=t2.Num and t2.Num=t3.Num
