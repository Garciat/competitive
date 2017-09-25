-- https://leetcode.com/problems/nth-highest-salary/

CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  declare M int;
  set M = N-1;
  RETURN (
      # Write your MySQL query statement below.
      
      select Salary from (select distinct Salary from Employee) as t1 order by Salary desc limit 1 offset M
  );
END
