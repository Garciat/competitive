-- https://leetcode.com/problems/department-highest-salary/

# Write your MySQL query statement below
select d.Name as Department, e.Name as Employee, e.Salary
from Employee e
join Department d on e.DepartmentId=d.Id
where not exists (select * from employee t1 where t1.DepartmentId=e.DepartmentId and t1.Salary>e.Salary)
