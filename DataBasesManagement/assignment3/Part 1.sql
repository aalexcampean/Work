USE Planner2
GO

DROP TABLE IF EXISTS LogTable 
CREATE TABLE LogTable(
	Lid INT IDENTITY PRIMARY KEY,
	TypeOperation VARCHAR(50),
	TableOperation VARCHAR(50),
	ExecutionDate DATETIME
);

GO

--use m:n relation Email- EmailAddress
SELECT * FROM Email
SELECT * FROM EmailAddress
SELECT * FROM sendTo
GO

CREATE OR ALTER FUNCTION ufValidateEmailAdr(@emailAdr VARCHAR(255))
RETURNS INT
AS
BEGIN
	DECLARE @return INT
	SET @return=1
	IF (@emailAdr IS NULL OR LEN(@emailAdr)<2)
	BEGIN
		SET @return=0
	END
	RETURN @return
END
GO

CREATE OR ALTER FUNCTION ufValidateContactId(@contactId INT)
RETURNS INT
AS
BEGIN
	DECLARE @return INT
	SET @return=1
	IF (@contactId IS NULL OR @contactId < 1)
	BEGIN
		SET @return=0
	END
	RETURN @return
END
GO

CREATE OR ALTER FUNCTION ufValidateSubject(@subject VARCHAR(255))
RETURNS INT
AS
BEGIN
	DECLARE @return INT
	SET @return=1
	IF (@subject IS NULL OR LEN(@subject)<1)
	BEGIN
		SET @return=0
	END
	RETURN @return
END
GO

CREATE OR ALTER PROCEDURE uspAddEmailAdr (@emailAdr VARCHAR(255), @contactId INT)
AS
	SET NOCOUNT ON
	IF (dbo.ufValidateEmailAdr(@emailAdr) <> 1)
	BEGIN
		RAISERROR('Email address is invalid',14,1)
	END
	IF (dbo.ufValidateContactId(@contactId) <> 1)
	BEGIN
		RAISERROR('Contact id is invalid',14,1)
	END
	INSERT INTO EmailAddress VALUES (@emailAdr,@contactId)
	INSERT INTO LogTable VALUES('add','EmailAdr',GETDATE())
GO

CREATE OR ALTER PROCEDURE uspAddEmail (@subject VARCHAR(255))
AS
	SET NOCOUNT ON
	IF (dbo.ufValidateSubject(@subject) <> 1)
	BEGIN
		RAISERROR('Subject is invalid',14,1)
	END
	INSERT INTO Email VALUES (@subject)
	INSERT INTO LogTable VALUES('add', 'email', GETDATE())
GO

CREATE OR ALTER PROCEDURE uspAddSentTo (@emailAdrId INT, @emailId INT)
AS
	SET NOCOUNT ON
	IF NOT EXISTS (SELECT * FROM EmailAddress WHERE Id = @emailAdrId)
	BEGIN
		RAISERROR('Invalid email address',14,1)
	END
	IF NOT EXISTS (SELECT * FROM Email WHERE Id = @emailId )
	BEGIN
		RAISERROR('Invalid email ',14,1)
	END
	INSERT INTO sendTo VALUES (@emailAdrId, @emailId)
	INSERT INTO LogTable VALUES('add','sendTo',GETDATE())
GO

CREATE OR ALTER PROCEDURE uspAddCommitScenario
AS
	BEGIN TRAN
	BEGIN TRY
		EXEC uspAddEmailAdr 'andreeaDeea@yahoo.com', 2
		EXEC uspAddEmail 'Invitatie zi de nastere'
		EXEC uspAddSentTo 14,9
		COMMIT TRAN
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		RETURN
	END CATCH
GO

CREATE OR ALTER PROCEDURE uspAddRollbackScenario
AS
	BEGIN TRAN
	BEGIN TRY
		EXEC uspAddEmailAdr 'andreeaDeea@yahoo.com', 2
		EXEC uspAddEmail ''
		EXEC uspAddSentTo 14,9
		COMMIT TRAN
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		RETURN
	END CATCH
GO

EXEC uspAddRollbackScenario
EXEC uspAddCommitScenario

SELECT * FROM LogTable

DELETE FROM Email WHERE Subject = 'Invitatie zi de nastere'
DELETE FROM sendTo WHERE Id = 12 or Id = 13
DELETE FROM EmailAddress WHERE EmailAdr = 'andreeaDeea@yahoo.com'