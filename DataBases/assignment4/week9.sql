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

-- view operating on 1 table
CREATE OR ALTER VIEW vOldestCamera AS
    SELECT C.id AS 'CameraId', C.model AS 'CameraModel', (SELECT MONTH(GETDATE()) - MONTH(C.dateOfPurchase)) AS 'Months had'
    FROM Camera C
    WHERE C.dateOfPurchase = (SELECT MAX(C2.dateOfPurchase)
        FROM Camera C2)
SELECT *
FROM vOldestCamera

-- view operating on 2 tables
CREATE OR ALTER VIEW vSentPhotoShootBatch AS
    SELECT PS.id AS 'PhotoShootId', PS.photoShootBatchId AS 'PhotoShootBatchId'
    FROM PhotoShoot PS
    WHERE photoShootBatchId IN (SELECT PSB.id
        FROM PhotoShootBatch PSB
        WHERE PSB.sent = 1 )
SELECT *
FROM vSentPhotoShootBatch

-- view operating on 2 tables and has a GROUP BY clause
CREATE OR ALTER VIEW vMostUsedCameras AS
    SELECT C2.id, C2.model, MAX(C2.NumberOfUses) AS 'NumberOfUses'
FROM (SELECT C.id, C.model, COUNT(C.id) AS NumberOfUses
    FROM Camera C
    INNER JOIN PhotoShootBatch PSB on C.id = PSB.cameraId
    INNER JOIN PhotoShoot PS on PSB.id = PS.photoShootBatchId
    GROUP BY C.id, C.model) C2
GROUP BY C2.id, C2.model, C2.NumberOfUses
HAVING C2.NumberOfUses = (SELECT MAX(C4.NumberOfUses1) AS 'NumberOfUses1'
        FROM (SELECT C3.id, COUNT(C3.id) AS NumberOfUses1
            FROM Camera C3
            INNER JOIN PhotoShootBatch PSB2 on C3.id = PSB2.cameraId
            INNER JOIN PhotoShoot PS2 on PSB2.id = PS2.photoShootBatchId
            GROUP BY C3.id) C4)
SELECT *
FROM vMostUsedCameras

