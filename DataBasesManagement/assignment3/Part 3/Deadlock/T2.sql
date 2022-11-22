USE Planner2
GO

--SELECT * FROM Email
--SELECT * FROM EmailAddress

--part 1
BEGIN TRAN
-- exclusive lock on table Email
UPDATE EmailAddress SET EmailAdr = 'Transaction 2' WHERE Id = 1
WAITFOR DELAY '00:00:10'

--this transaction will be blocked, because T1 already has an exclusive lock on Email
UPDATE Email SET Subject = 'Transaction 2' WHERE Id = 5
COMMIT TRAN

--this transaction will be chosen as the deadlock victim 
--and it will terminate with an error
--the tables will contain the values from T1