-- https://leetcode.com/problems/second-highest-salary/

# Write your MySQL query statement below
select (select * from (select distinct Salary from Employee order by Salary desc) as t limit 1, 1) as SecondHighestSalary;
