USE CarService
GO

--part 2: we can read uncommited data (dirty read)
SET TRAN ISOLATION LEVEL READ UNCOMMITTED
BEGIN TRAN
--see update
SELECT * FROM Car
WAITFOR DELAY '00:00:05'
--update was rolled back
SELECT * FROM Car
COMMIT TRAN