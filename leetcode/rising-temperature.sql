-- https://leetcode.com/problems/rising-temperature/

# Write your MySQL query statement below
select w1.Id
from Weather w1
join Weather w2 on w1.Date = date_add(w2.Date, interval 1 day) and w1.Temperature > w2.Temperature
