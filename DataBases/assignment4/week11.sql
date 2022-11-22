USE CampeonPhotography

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

-- preparing the tables
DROP TABLE PhotoShootLocation
DROP TABLE Location
DROP TABLE Lens

CREATE TABLE Location(
  id INT NOT NULL,
  name VARCHAR(50) NOT NULL,
  address VARCHAR(50) NOT NULL,
  CONSTRAINT pk_Location PRIMARY KEY (id, name)
);
GO

CREATE TABLE PhotoShootLocation(
  id INT NOT NULL PRIMARY KEY IDENTITY(1,1),
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
        WHERE L.address LIKE 'https://%')
GO

SELECT *
FROM vPhotoShootAtAddress
GO


CREATE OR ALTER PROC runViewTest(@givenViewName VARCHAR(100)) AS
BEGIN
   DECLARE @runViewTestCommand NVARCHAR(200)
    SET @runViewTestCommand = 'SELECT * FROM ' + @givenViewName
    EXEC @runViewTestCommand
END

CREATE OR ALTER PROC runDeleteTableTest(@givenTable VARCHAR(100), @deletedNrOfRows INT) AS
BEGIN
   DECLARE @runDeleteTableTest NVARCHAR(200)
    SET @runDeleteTableTest = 'DELETE FROM ' + @givenTable + ' WHERE id <= ' + @deletedNrOfRows
    EXEC @runDeleteTableTest
END

CREATE OR ALTER PROC runInsertTest(@givenView VARCHAR(100)) AS
BEGIN
   DECLARE @runViewTestCommand NVARCHAR(200)
    SET @runViewTestCommand = 'SELECT * FROM ' + @givenView
    EXEC @runViewTestCommand
END

