-- https://leetcode.com/problems/trips-and-users/

# Write your MySQL query statement below
select
    Trips.Request_at as Day,
    round(sum(if(Trips.Status <> 'completed', 1, 0)) / count(*), 2) as `Cancellation Rate`
from Trips
join Users on Trips.Client_Id = Users.Users_Id and Users.Banned = 'No'
where Trips.Request_at between '2013-10-01' and '2013-10-03'
group by Trips.Request_at
