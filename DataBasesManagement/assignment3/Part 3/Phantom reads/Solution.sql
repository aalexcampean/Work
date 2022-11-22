USE Planner2
GO

--solution: set transaction isolation level to serializable
SET TRAN ISOLATION LEVEL SERIALIZABLE
BEGIN TRAN
SELECT * FROM Email
WAITFOR DELAY '00:00:05'
SELECT * FROM Email
COMMIT TRAN