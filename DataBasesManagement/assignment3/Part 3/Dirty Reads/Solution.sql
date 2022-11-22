USE Planner2
GO

--solution: set transaction isolation level to read commited
SET TRAN ISOLATION LEVEL READ COMMITTED
BEGIN TRAN
SELECT * FROM Email
WAITFOR DELAY '00:00:05'
SELECT * FROM Email
COMMIT TRAN