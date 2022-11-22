USE Planner2
GO

--solution: set deadlock priority to high for the second transaction
--now, T1 will be chosen as the deadlock victim, as it has a lower priority
--default priority is normal (0)

SET DEADLOCK_PRIORITY HIGH
BEGIN TRAN
-- exclusive lock on table Allergens
UPDATE Email SET Subject = 'Transaction 2' WHERE Id = 5
WAITFOR DELAY '00:00:10'

UPDATE EmailAddress SET EmailAdr = 'Transaction 2' WHERE Id = 5
COMMIT TRAN