-- https://leetcode.com/problems/delete-duplicate-emails/

# Write your MySQL query statement below
delete from Person
where Email in
(select Email
from (select * from Person) t1
group by Email
having count(*) > 1)
and Id not in (select min(Id)
from (select * from Person) t2
group by Email
having count(*) > 1)
