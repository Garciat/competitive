-- https://leetcode.com/problems/customers-who-never-order/

# Write your MySQL query statement below
select Name as Customers
from Customers
where not exists (select * from Orders where Customers.Id=CustomerId)
