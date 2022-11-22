USE Planner2
GO

CREATE OR ALTER PROCEDURE uspAddEmailRecover (@subject VARCHAR(255))
AS
	SET NOCOUNT ON
	BEGIN TRAN
	BEGIN TRY
		IF (dbo.ufValidateSubject(@subject) <> 1)
		BEGIN
			RAISERROR('Subject is invalid',14,1)
		END
		IF EXISTS (SELECT * FROM Email WHERE Subject= @subject)
		BEGIN
			RAISERROR('Email with this subject already exists',14,1)
		END
		INSERT INTO Email VALUES (@subject)
		INSERT INTO LogTable VALUES('add','email',GETDATE())
		COMMIT TRAN
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
	END CATCH
GO

CREATE OR ALTER PROCEDURE uspAddAEmailAddrRecover (@emailAdr VARCHAR(255), @contactId INT)
AS
	SET NOCOUNT ON
	BEGIN TRAN
	BEGIN TRY
		IF (dbo.ufValidateEmailAdr(@emailAdr) <> 1)
		BEGIN
			RAISERROR('Email address is invalid', 14, 1)
		END
		IF NOT EXISTS (SELECT * FROM Contact WHERE Id = @contactId)
		BEGIN
			RAISERROR('No contact with this id ', 14, 1)
		END
		IF (dbo.ufValidateContactId(@contactId) <> 1)
		BEGIN
			RAISERROR('Contact id is invalid', 14, 1)
		END
		INSERT INTO EmailAddress VALUES (@emailAdr, @contactId)
		INSERT INTO LogTable VALUES('add', 'emailAdr', GETDATE())
		COMMIT TRAN
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
	END CATCH
GO

CREATE OR ALTER PROCEDURE uspAddSendToRecover (@emailAdrId INT, @emailId INT)
AS
	SET NOCOUNT ON
	BEGIN TRAN
	BEGIN TRY
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
		COMMIT TRAN
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
	END CATCH
GO

CREATE OR ALTER PROCEDURE uspBadAddScenario
AS
	EXEC uspAddEmailRecover 'Surpriza Cristina'
	EXEC uspAddAEmailAddrRecover '', 40 --this will fail, but the item added before will still be in the database
	EXEC uspAddSendToRecover 10,10
GO

CREATE OR ALTER PROCEDURE uspGoodAddScenario
AS
	EXEC uspAddEmailRecover 'Surpriza Alexandra'
	EXEC uspAddAEmailAddrRecover 'chetan_anca@gmail.com', 2 
	EXEC uspAddSendToRecover 24, 11
GO

EXEC uspBadAddScenario
SELECT * FROM LogTable

EXEC uspGoodAddScenario
SELECT * FROM LogTable

SELECT * FROM Email
SELECT * FROM EmailAddress
SELECT * FROM sendTo
