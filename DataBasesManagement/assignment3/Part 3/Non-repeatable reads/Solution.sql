USE Planner2
GO

--solution: set transaction isolation level to repeatable read
SET TRAN ISOLATION LEVEL REPEATABLE READ
BEGIN TRAN
SELECT * FROM Email
WAITFOR DELAY '00:00:05'
--now we see the value before the update 
SELECT * FROM Email
COMMIT TRAN
