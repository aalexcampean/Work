USE Planner2
GO

--part 1
INSERT INTO Email(Subject) VALUES ('vreau vacanta')
BEGIN TRAN
WAITFOR DELAY '00:00:04'
UPDATE Email 
SET Subject = 'ai examene'
WHERE Subject = 'vreau vacanta'
COMMIT TRAN