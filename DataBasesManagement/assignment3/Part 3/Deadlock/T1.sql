USE Planner2
GO

--SELECT * FROM MenuItem
--SELECT * FROM Allergens

--part 1
BEGIN TRAN
--exclusive lock on table Email
UPDATE Email SET Subject = 'Transaction 1' WHERE Id = 5
WAITFOR DELAY '00:00:10'

--this transaction will be blocked, because T2 already has an exclusive lock on Allergens
UPDATE EmailAddress SET EmailAdr = 'Transaction 1' WHERE Id = 1
COMMIT TRAN