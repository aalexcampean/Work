USE CampeonPhotography
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_Tables
GO
if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tables
GO
if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_TestRuns
GO
if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_TestRuns
GO
if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tests
GO
if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Tests
GO
if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_Views
GO
if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Views
GO
if exists (select * from dbo.sysobjects where id = object_id(N'[Tables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Tables]
GO
if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRunTables]
GO
if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRunViews]
GO
if exists (select * from dbo.sysobjects where id = object_id(N'[TestRuns]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRuns]
GO
if exists (select * from dbo.sysobjects where id = object_id(N'[TestTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestTables]
GO
if exists (select * from dbo.sysobjects where id = object_id(N'[TestViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestViews]
GO
if exists (select * from dbo.sysobjects where id = object_id(N'[Tests]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Tests]
GO
if exists (select * from dbo.sysobjects where id = object_id(N'[Views]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Views]
GO


-- TABLE CREATION

CREATE TABLE Tables (
	TableID INT IDENTITY (1, 1) NOT NULL ,
	NAME NVARCHAR(50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL
) ON [PRIMARY]
GO


CREATE TABLE TestRunTables (
	TestRunID INT NOT NULL ,
	TableID INT NOT NULL ,
	StartAt DATETIME NOT NULL ,
	EndAt DATETIME NOT NULL
) ON [PRIMARY]
GO


CREATE TABLE TestRunViews (
	TestRunID INT NOT NULL ,
	ViewID INT NOT NULL ,
	StartAt DATETIME NOT NULL ,
	EndAt DATETIME NOT NULL
) ON [PRIMARY]
GO


CREATE TABLE TestRuns (
	TestRunID INT IDENTITY (1, 1) NOT NULL ,
	Description NVARCHAR(2000) COLLATE SQL_Latin1_General_CP1_CI_AS NULL ,
	StartAt DATETIME NULL ,
	EndAt DATETIME NULL
) ON [PRIMARY]
GO


CREATE TABLE TestTables (
	TestID INT NOT NULL ,
	TableID INT NOT NULL ,
	NoOfRows INT NOT NULL ,
	Position INT NOT NULL
) ON [PRIMARY]
GO


CREATE TABLE TestViews (
	TestID INT NOT NULL ,
	ViewID INT NOT NULL
) ON [PRIMARY]
GO


CREATE TABLE Tests (
	TestID INT IDENTITY (1, 1) NOT NULL ,
	Name NVARCHAR(50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL
) ON [PRIMARY]
GO


CREATE TABLE Views (
	ViewID INT IDENTITY (1, 1) NOT NULL ,
	Name NVARCHAR(50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL
) ON [PRIMARY]
GO

-- PRIMARY KEY CONSTRAINTS

ALTER TABLE Tables WITH NOCHECK ADD
    CONSTRAINT [PK_Tables] PRIMARY KEY CLUSTERED (TableID)  ON [PRIMARY]
GO


ALTER TABLE TestRunTables WITH NOCHECK ADD
    CONSTRAINT [PK_TestRunTables] PRIMARY KEY CLUSTERED (TestRunID, TableID)  ON [PRIMARY]
GO


ALTER TABLE [TestRunViews] WITH NOCHECK ADD
    CONSTRAINT [PK_TestRunViews] PRIMARY KEY CLUSTERED (TestRunID, ViewID)  ON [PRIMARY]
GO


ALTER TABLE TestRuns WITH NOCHECK ADD
    CONSTRAINT [PK_TestRuns] PRIMARY KEY CLUSTERED (TestRunID)  ON [PRIMARY]
GO


ALTER TABLE TestTables WITH NOCHECK ADD
    CONSTRAINT [PK_TestTables] PRIMARY KEY  CLUSTERED (TestID, TableID)  ON [PRIMARY]
GO


ALTER TABLE TestViews WITH NOCHECK ADD
    CONSTRAINT [PK_TestViews] PRIMARY KEY  CLUSTERED (TestID, ViewID)  ON [PRIMARY]
GO


ALTER TABLE Tests WITH NOCHECK ADD
    CONSTRAINT [PK_Tests] PRIMARY KEY  CLUSTERED (TestID)  ON [PRIMARY]
GO


ALTER TABLE Views WITH NOCHECK ADD
    CONSTRAINT [PK_Views] PRIMARY KEY  CLUSTERED (ViewID)  ON [PRIMARY]
GO

-- FOREIGN KEY CONSTRAINTS

ALTER TABLE TestRunTables ADD
	CONSTRAINT [FK_TestRunTables_Tables] FOREIGN KEY (TableID) REFERENCES Tables (TableID) ON DELETE CASCADE  ON UPDATE CASCADE,
    CONSTRAINT [FK_TestRunTables_TestRuns] FOREIGN KEY (TestRunID) REFERENCES TestRuns (TestRunID) ON DELETE CASCADE  ON UPDATE CASCADE
GO


ALTER TABLE TestRunViews ADD
    CONSTRAINT [FK_TestRunViews_TestRuns] FOREIGN KEY (TestRunID) REFERENCES TestRuns (TestRunID) ON DELETE CASCADE  ON UPDATE CASCADE,
    CONSTRAINT [FK_TestRunViews_Views] FOREIGN KEY (ViewId) REFERENCES Views (ViewID) ON DELETE CASCADE  ON UPDATE CASCADE
GO


ALTER TABLE TestTables ADD
    CONSTRAINT [FK_TestTables_Tables] FOREIGN KEY (TableID) REFERENCES Tables (TableID) ON DELETE CASCADE  ON UPDATE CASCADE,
    CONSTRAINT [FK_TestTables_Tests] FOREIGN KEY (TestID) REFERENCES Tests (TestID) ON DELETE CASCADE  ON UPDATE CASCADE
GO


ALTER TABLE TestViews ADD
    CONSTRAINT [FK_TestViews_Tests] FOREIGN KEY (TestID) REFERENCES Tests (TestID),
    CONSTRAINT FK_TestViews_Views FOREIGN KEY (ViewID) REFERENCES Views (ViewID)
GO

DROP TABLE PhotoShootLocation
DROP TABLE Location
DROP TABLE Lens

-- creating the tables

CREATE TABLE Location(
  id INT NOT NULL,
  name VARCHAR(50) NOT NULL,
  address VARCHAR(50) NOT NULL,
  CONSTRAINT pk_Location PRIMARY KEY (id, name)
);
GO

CREATE TABLE PhotoShootLocation(
  id INT NOT NULL PRIMARY KEY,
  photoShootId INT NOT NULL,
  locationId INT NOT NULL,
  locationName VARCHAR(50) NOT NULL,
  CONSTRAINT fk_PhotoShoot FOREIGN KEY (photoShootId) REFERENCES PhotoShoot(id),
  CONSTRAINT fk_Location FOREIGN KEY (locationId, locationName) REFERENCES Location(id, name)
);
GO

CREATE TABLE Lens(
    id INT NOT NULL,
    model VARCHAR(50) NOT NULL,
    dateOfPurchase DATE,
    CONSTRAINT pk_Lens PRIMARY KEY (id)
);
GO



CREATE TABLE Cinema(
    id INT NOT NULL,
    name VARCHAR(100) NOT NULL,
    location VARCHAR(50) NOT NULL,
    movieId INT NOT NULL,
    CONSTRAINT pk_Cinema PRIMARY KEY (id),
    CONSTRAINT fk_CinemaMovie FOREIGN KEY (movieId) REFERENCES Movie(id)
)

CREATE TABLE Movie(
    id INT NOT NULL,
    name VARCHAR(100) NOT NULL,
    genre VARCHAR(20) NOT NULL,
    duration INT NOT NULL,
    description VARCHAR(200),
    CONSTRAINT pk_Movie PRIMARY KEY (id),
)


SELECT *
FROM Movie M
INNER JOIN Cinema C2 on M.id = C2.movieId
WHERE M.genre = 'romance' AND C2.id NOT IN (SELECT C.id
    FROM Cinema C
    WHERE C.location != 'Clacton-on-Sea')

-- creating the Views

-- view operating on 1 table
CREATE OR ALTER VIEW vOldestLens AS
    SELECT L.id AS 'LensId', L.model AS 'LensModel', (SELECT MONTH(GETDATE()) - MONTH(L.dateOfPurchase)) AS 'Months had'
    FROM Lens L
    WHERE L.dateOfPurchase = (SELECT MAX(L2.dateOfPurchase)
        FROM Lens L2)
GO

SELECT *
FROM vOldestLens
GO

CREATE OR ALTER VIEW vModelStartingWith1 AS
    SELECT L.id AS 'LensId', L.model AS 'LensModel'
    FROM Lens L
    WHERE L.model LIKE '%Model 1%'
GO

SELECT *
FROM vModelStartingWith1
GO

-- view operating on at least 2 tables
CREATE OR ALTER VIEW vPhotographerShotAtLocation AS
    SELECT P.id, P.name
    FROM Photographer P, PhotoShoot Ph, PhotoShootLocation Pl, Location L
    WHERE (P.id = Ph.photographerId AND Pl.photoShootId = Ph.id
           AND PL.locationId = L.id AND L.name LIKE '%a%')
GO

SELECT *
FROM vPhotographerShotAtLocation
GO

-- view operating on at least 2 tables and has a GROUP BY clause
CREATE OR ALTER VIEW vPhotoShootAtAddress AS
    SELECT PSL.photoShootId AS 'PhotoShootId', PS.photographerId AS 'PhotographerId'
    FROM PhotoShootLocation PSL
    INNER JOIN PhotoShoot PS on PS.id = PSL.photoShootId
    GROUP BY PSL.id, PSL.photoShootId, PS.photographerId
    HAVING PSL.id = ANY(SELECT PSL2.id
        FROM PhotoShootLocation PSL2
        INNER JOIN Location L on L.id = PSL2.locationId
        WHERE L.address LIKE 'Address 4%')
GO

SELECT *
FROM vPhotoShootAtAddress
GO

-- creating the auxiliary tests (insert/delete/run view)

-- the procedure that runs the test for the views
CREATE OR ALTER PROC runViewTest(@givenViewName VARCHAR(100)) AS
BEGIN
   DECLARE @runViewTestCommand NVARCHAR(200)
    SET @runViewTestCommand = 'SELECT * FROM ' + @givenViewName
    EXEC (@runViewTestCommand)
END
GO

-- the procedure that runs the test for the deletes
CREATE OR ALTER PROC runDeleteTableTest(@givenTableName NVARCHAR(100), @deletedNrOfRows INT) AS
BEGIN
   DECLARE @runDeleteTableTest NVARCHAR(200)
   DECLARE @count INT
   SET @count = 1

   WHILE @count <= @deletedNrOfRows
       BEGIN
           SET @runDeleteTableTest = 'DELETE TOP (1) FROM ' + @givenTableName
           EXEC (@runDeleteTableTest)

           SET @count = @count + 1
        END
END
GO

-- the procedure that runs the test for the inserts
CREATE OR ALTER PROC runInsertTest(@givenTableName VARCHAR(100), @insertedNrOfRows INT) AS
BEGIN
    -- using a counter to insert the correct number of rows
    DECLARE @count INT
    SET @count = 1

    -- declaring the variables used for the insertion of data into the table Location
    DECLARE @pkLocationId INT
    DECLARE @locationName VARCHAR(50)
    DECLARE @locationAddress VARCHAR(50)

    -- declaring the variables used for the insertion of data into the table PhotoShootLocation
    DECLARE @pkPhotoSLocationId INT
    DECLARE @fkPhotoSId INT
    DECLARE @fkLocationId INT
    DECLARE @fkLocationName VARCHAR(50)

    -- declaring the variables used for the insertion of data into the table Lens
    DECLARE @pkLensId INT
    DECLARE @lensModel VARCHAR(50)
    DECLARE @lensDateOfPurchase DATE

    WHILE @count <= @insertedNrOfRows
        BEGIN
            IF @givenTableName = 'Location'
            BEGIN
                SET @pkLocationId = @count
                SET @locationName = 'Location ' + CONVERT(VARCHAR(50), @count)
                SET @locationAddress = 'Address ' + CONVERT(VARCHAR(50), @count)
                INSERT INTO Location(id, name, address) VALUES (@pkLocationId, @locationName, @locationAddress)
            END

            IF @givenTableName = 'PhotoShootLocation'
            BEGIN
                SET @pkPhotoSLocationId = @count
                SELECT TOP 1 @fkPhotoSId = id FROM PhotoShoot ORDER BY NEWID()
                SELECT TOP 1 @fkLocationId = id, @fkLocationName = name FROM Location ORDER BY NEWID()
                INSERT INTO PhotoShootLocation(id, photoShootId, locationId, locationName) VALUES (@pkPhotoSLocationId, @fkPhotoSId, @fkLocationId, @fkLocationName)
            END

            IF @givenTableName = 'Lens'
            BEGIN
                SET @pkLensId = @count
                SET @lensModel = 'Model ' + CONVERT(VARCHAR(50), @count)
                SET @lensDateOfPurchase  = DATEADD(DAY, ABS(CHECKSUM(NEWID()) % 1064),'2019-01-01')
                INSERT INTO Lens(id, model, dateOfPurchase) VALUES (@pkLensId, @lensModel, @lensDateOfPurchase)
            END

            SET @count = @count + 1
        END
END
GO

-- creating the procedures that populate the Tables, Views and Tests

CREATE OR ALTER PROC addToViews(@givenViewName VARCHAR(50)) AS
BEGIN
    IF @givenViewName IN (SELECT Name FROM Views) BEGIN
        PRINT 'Name already exists in Views'
        RETURN
    END

    IF @givenViewName NOT IN (SELECT TABLE_NAME FROM INFORMATION_SCHEMA.VIEWS WHERE TABLE_SCHEMA = 'dbo') BEGIN
        PRINT 'View does not exist in the database'
        RETURN
    END

    INSERT INTO Views(Name) VALUES (@givenViewName)
END
GO

CREATE OR ALTER PROC addToTables(@givenTableName VARCHAR(50)) AS
BEGIN
    IF @givenTableName IN (SELECT NAME FROM Tables) BEGIN
        PRINT 'Name already exists in Tables'
        RETURN
    END

    IF @givenTableName NOT IN (SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = 'dbo') BEGIN
        PRINT 'Table does not exist in the database'
        RETURN
    END

    INSERT INTO Tables(NAME) VALUES (@givenTableName)
END
GO

CREATE OR ALTER PROC addToTests(@givenTestName VARCHAR(50)) AS
BEGIN
    IF @givenTestName IN (SELECT Name FROM Tests) BEGIN
        PRINT 'Name already exists in Test'
        RETURN
    END

    INSERT INTO Tests(Name) VALUES (@givenTestName)
END
GO

-- creating the procedures that populate the TestTables and ViewTables

CREATE OR ALTER PROC linkTablesToTests(@givenTestName VARCHAR(50), @givenTableName VARCHAR(50), @nrOfRows INT, @position INT) AS
BEGIN
    IF @givenTestName NOT IN (SELECT Name FROM Tests) BEGIN
            PRINT 'Name does not exist in Tests'
            RETURN
    END

    IF @givenTableName NOT IN (SELECT Name FROM Tables) BEGIN
        PRINT 'Name does not exist in Tables'
        RETURN
    END

    IF EXISTS(SELECT * FROM TestTables JOIN dbo.Tests T on TestTables.TestID = T.TestID WHERE T.Name = @givenTestName AND TestTables.Position = @position) BEGIN
        PRINT ('Incorrect given position, conflicting with the already existing ones')
        RETURN
    end

    INSERT INTO TestTables (TestID, TableID, NoOfRows, Position) VALUES (
        (SELECT TestID FROM Tests WHERE Name = @givenTestName),
        (SELECT TableID FROM Tables WHERE NAME = @givenTableName),
        @nrOfRows,
        @position
        )
END
GO

CREATE OR ALTER PROC linkViewsToTests(@givenTestName VARCHAR(50), @givenViewName VARCHAR(50)) AS
BEGIN
    IF @givenTestName NOT IN (SELECT Name FROM Tests) BEGIN
            PRINT 'Name does not exist in Tests'
            RETURN
    END

    IF @givenViewName NOT IN (SELECT Name FROM Views) BEGIN
        PRINT 'Name does not exist in Views'
        RETURN
    END

    INSERT INTO TestViews (TestID, ViewID) VALUES (
        (SELECT TestID FROM Tests WHERE Name = @givenTestName),
        (SELECT ViewID FROM Views WHERE Name = @givenViewName)
        )
END
GO

-- populating the Tables
EXEC addToTables PhotoShootLocation
GO
EXEC addToTables Location
GO
EXEC addToTables Lens
GO

-- populating the Views
EXEC addToViews vPhotoShootAtAddress
GO
EXEC addToViews vPhotographerShotAtLocation
GO
EXEC addToViews vOldestLens
GO
EXEC addToViews vModelStartingWith1
GO

-- populating the Tests
EXEC addToTests test1
GO
EXEC addToTests test2
GO
EXEC addToTests test3
GO

-- creating test1
EXEC linkTablesToTests test1, Location, 1000, 1
GO
EXEC linkTablesToTests test1, PhotoShootLocation, 1000, 2
GO
EXEC linkViewsToTests test1, vPhotoShootAtAddress
GO

-- creating test2
EXEC linkTablesToTests test2, Location, 1000, 1
GO
EXEC linkTablesToTests test2, PhotoShootLocation, 1000, 2
GO
EXEC linkViewsToTests test2, vPhotographerShotAtLocation
GO

-- creating test3
EXEC linkTablesToTests test3, Lens, 1000, 1
GO
EXEC linkViewsToTests test3, vOldestLens
GO
EXEC linkViewsToTests test3, vModelStartingWith1
GO

-- the procedure that executes the Tests
CREATE OR ALTER PROC runTest(@givenTestName VARCHAR(50)) AS
BEGIN
    IF @givenTestName NOT IN(SELECT Name FROM Tests) BEGIN
        PRINT('Name does not exist in Tests')
        RETURN
    END

    -- the time stamps used for determining the test's time of execution
    DECLARE @startAllTime datetime2
    DECLARE @endAllTime datetime2
    DECLARE @startTime datetime2
    DECLARE @endTime datetime2

    -- the variables used to store the tables/view/rows/position
    DECLARE @tableName VARCHAR(50)
    DECLARE @viewName VARCHAR(50)
    DECLARE @nrOfRows INT
    DECLARE @position INT

    -- the id og the testRun
    DECLARE @testRunId INT
	SET @testRunId = (SELECT MAX(TestRunId) + 1 from TestRuns)
	IF @testRunId IS NULL
		SET @testRunId = 0

    -- the id of the test
    DECLARE @testId INT
    SELECT @testId = TestID FROM Tests WHERE Name = @givenTestName

    -- a cursor used for parsing the tables used in the test
    DECLARE tableCursor CURSOR SCROLL
        FOR
            SELECT Tables.Name, TT.NoOfRows, TT.Position
            FROM Tables JOIN dbo.TestTables TT on Tables.TableID = TT.TableID
            WHERE TT.TestID = @testId
            ORDER BY TT.Position

    --a cursor used for parsing the views used in the test
    DECLARE viewCursor CURSOR
        FOR
            SELECT Views.Name
            FROM Views JOIN dbo.TestViews TV on Views.ViewID = TV.ViewID
            WHERE TV.TestID = @testId

    -- setting the timestamp for the start of the test
    SET @startAllTime = SYSDATETIME()

    -- insert the data regarding the entire test into TestRuns
    SET IDENTITY_INSERT TestRuns ON
    INSERT INTO TestRuns(TestRunID, description, startat)VALUES (@testRunId, 'Running ' + @givenTestName, @startAllTime)
    SET IDENTITY_INSERT TestRuns OFF

    -- perform the deletes
    OPEN tableCursor
    FETCH LAST FROM tableCursor INTO @tableName, @nrOfRows, @position
    WHILE @@FETCH_STATUS = 0 BEGIN
        EXEC runDeleteTableTest @tableName, @nrOfRows
        FETCH PRIOR FROM tableCursor INTO @tableName, @nrOfRows, @position
    END
    CLOSE tableCursor

    -- perform the inserts
    OPEN tableCursor
    FETCH FIRST FROM tableCursor INTO @tableName, @nrOfRows, @position
    WHILE @@FETCH_STATUS = 0 BEGIN
        SET @startTime = SYSDATETIME()
        EXEC runInsertTest @tableName, @nrOfRows
        SET @endTime = SYSDATETIME()
        -- insert the collected data about the inserts into the TestRunTables
        INSERT INTO TestRunTables(testrunid, tableid, startat, endat) VALUES (@testRunId, (SELECT TableID FROM Tables WHERE Name = @tableName), @startTime, @endTime)
        FETCH NEXT FROM tableCursor INTO @tableName, @nrOfRows, @position
    END
    CLOSE tableCursor
    DEALLOCATE tableCursor

    -- perform the views
    OPEN viewCursor
    FETCH NEXT FROM viewCursor INTO @viewName
    WHILE @@FETCH_STATUS = 0 BEGIN
        SET @startTime = SYSDATETIME()
        EXEC runViewTest @viewName
        SET @endTime = SYSDATETIME()
        -- insert the collected data about the view into the TestRunViews
        INSERT INTO TestRunViews(testrunid, viewid, startat, endat) VALUES (@testRunId, (SELECT ViewID FROM Views WHERE Name = @viewName), @startTime, @endTime)
        FETCH NEXT FROM viewCursor INTO @viewName
    END
    CLOSE viewCursor
    DEALLOCATE viewCursor

    -- setting the timestamp for the end of the test
    SET @endAllTime = SYSDATETIME()

    -- updating the endTime for the TestRun
    UPDATE TestRuns
    SET EndAt = @endAllTime
    WHERE TestRunID = @testRunId

END
GO

-- running the tests
EXEC runTest 'test1'
GO
EXEC runTest 'test2'
GO
EXEC runTest 'test3'
GO

SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews


