USE Planner2
GO

--DELETE FROM Email WHERE Subject='mda'
--SELECT * FROM Email

--part 1
BEGIN TRAN
WAITFOR DELAY '00:00:04'
INSERT INTO Email(Subject) VALUES ('mda')
COMMIT TRAN