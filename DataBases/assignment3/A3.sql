USE CampeonPhotography

-- a. modify the type of a column;
-- b. add / remove a column;
-- c. add / remove a DEFAULT constraint;
-- d. add / remove a primary key;
-- e. add / remove a candidate key;
-- f. add / remove a foreign key;
-- g. create / drop a table.

CREATE TABLE Package(
    id INT NOT NULL PRIMARY KEY IDENTITY(1,1),
    name VARCHAR(50) NOT NULL,
    pricing INT
);
GO

CREATE TABLE Lens(
    id INT NOT NULL IDENTITY(1,1),
    model VARCHAR(50) NOT NULL,
    dateOfPurchase DATE
);
GO


CREATE TABLE UsedLens(
    id INT NOT NULL PRIMARY KEY IDENTITY(1,1),
    lensId INT NOT NULL,
    photoShootBatchId INT NOT NULL
);
GO

ALTER TABLE UsedLens
ADD FOREIGN KEY (photoShootBatchId) REFERENCES PhotoShootBatch(id)
GO

-- a. modify the type of a column;

CREATE OR ALTER PROC changePackagePricingTypeToFloat
AS
    ALTER TABLE Package
    ALTER COLUMN pricing FLOAT
GO

CREATE OR ALTER PROC changePackagePricingTypeToInt
AS
    ALTER TABLE Package
    ALTER COLUMN pricing INT
GO

EXEC changePackagePricingTypeToFloat
EXEC changePackagePricingTypeToInt

-- b. add / remove a column;

CREATE OR ALTER PROC addPhotographerDateOfEmploymentField
AS
    ALTER TABLE Photographer
    ADD data_of_employment DATE
GO

CREATE OR ALTER PROC dropPhotographerDateOfEmploymentField
AS
    ALTER TABLE Photographer
    DROP COLUMN data_of_employment
GO

EXEC addPhotographerDateOfEmploymentField
EXEC dropPhotographerDateOfEmploymentField

-- c. add / remove a DEFAULT constraint;

CREATE OR ALTER PROC addDefaultLocation
AS
    ALTER TABLE Location
    ADD CONSTRAINT df_address
    DEFAULT '' FOR address
GO

CREATE OR ALTER PROC removeDefaultLocation
AS
    ALTER TABLE Location
    DROP CONSTRAINT df_address
GO

EXEC addDefaultLocation
EXEC removeDefaultLocation

-- d. add / remove a primary key;

CREATE OR ALTER PROC addLensPrimaryKey
AS
    ALTER TABLE Lens
    ADD CONSTRAINT pk_Lens PRIMARY KEY (id, model)
    PRINT 'the procedure addLensPrimaryKey was created'
GO

CREATE OR ALTER PROC removeLensPrimaryKey
AS
    ALTER TABLE Lens
    DROP CONSTRAINT pk_Lens
    PRINT 'the procedure removeLensPrimaryKey was created'
GO

EXEC addLensPrimaryKey
EXEC removeLensPrimaryKey

-- e. add / remove a candidate key;

CREATE OR ALTER PROC addPackageCandidateKey
AS
    ALTER TABLE Package
    ADD CONSTRAINT ck_Package UNIQUE (id, name, pricing)
    PRINT 'the procedure addPackageCandidateKey was created'
GO

CREATE OR ALTER PROC removePackageCandidateKey
AS
    ALTER TABLE Package
    DROP CONSTRAINT ck_Package
    PRINT 'the procedure removePackageCandidateKey was created'
GO

EXEC addPackageCandidateKey
EXEC removePackageCandidateKey

-- f. add / remove a foreign key;

ALTER TABLE UsedLens
ADD lensModel VARCHAR(50) DEFAULT ''
GO

CREATE OR ALTER PROC addUsedLensForeignKeys
AS
    ALTER TABLE UsedLens
    ADD CONSTRAINT fk_LensUsedLens
    FOREIGN KEY (lensId, lensModel) REFERENCES Lens(id, model)
GO

CREATE OR ALTER PROC removeUsedLensForeignKeys
AS
    ALTER TABLE UsedLens
    DROP CONSTRAINT fk_LensUsedLens
GO

EXEC addUsedLensForeignKeys
EXEC removeUsedLensForeignKeys

-- g. create / drop a table.

CREATE OR ALTER PROC dropPackageTable
AS
    DROP TABLE Package
GO

CREATE OR ALTER PROC createPackageTable
AS
    CREATE TABLE Package(
    id INT NOT NULL PRIMARY KEY IDENTITY(1,1),
    name VARCHAR(50) NOT NULL,
    pricing FLOAT,
    CONSTRAINT ck_Package UNIQUE (id, name, pricing));
GO

EXEC dropPackageTable
EXEC createPackageTable

-- create the dataBase version table / insert your procedures

CREATE TABLE DbVersion(
    targetVersion INT UNIQUE NOT NULL,
    procedureName VARCHAR(50) DEFAULT '',
    undoProcedureName VARCHAR(50) DEFAULT '',
    currentVersion INT DEFAULT 0
);
GO

INSERT INTO DbVersion (targetVersion, currentVersion) VALUES (0, 1)
INSERT INTO DbVersion (targetVersion, procedureName, undoProcedureName) VALUES (1, 'changePackagePricingTypeToFloat', 'changePackagePricingTypeToInt')
INSERT INTO DbVersion (targetVersion, procedureName, undoProcedureName) VALUES (2, 'addPhotographerDateOfEmploymentField', 'dropPhotographerDateOfEmploymentField')
INSERT INTO DbVersion (targetVersion, procedureName, undoProcedureName) VALUES (3, 'addDefaultLocation', 'removeDefaultLocation')
INSERT INTO DbVersion (targetVersion, procedureName, undoProcedureName) VALUES (4, 'addLensPrimaryKey', 'removeLensPrimaryKey')
INSERT INTO DbVersion (targetVersion, procedureName, undoProcedureName) VALUES (5, 'addPackageCandidateKey', 'removePackageCandidateKey')
INSERT INTO DbVersion (targetVersion, procedureName, undoProcedureName) VALUES (6, 'addUsedLensForeignKeys', 'removeUsedLensForeignKeys')
INSERT INTO DbVersion (targetVersion, procedureName, undoProcedureName) VALUES (7, 'dropPackageTable', 'createPackageTable')
GO


-- SELECT *
-- FROM Package
--
-- EXEC databaseVersion 1


-- the main procedure that takes the database to a desired state

CREATE OR ALTER PROC databaseVersion(@givenVersion INT) AS
BEGIN
    IF @givenVersion < 0 OR @givenVersion > 7
        BEGIN
            RAISERROR ('Such version does not exist', 10, 1)
        END
    ELSE
        BEGIN
            DECLARE @currentVersion INT
            SELECT @currentVersion = targetVersion
            FROM DbVersion dbV
            WHERE dbV.currentVersion = 1

            IF @givenVersion = @currentVersion
                BEGIN
                   RAISERROR ('Given version is the current one', 10, 1)
                END
            ELSE
                BEGIN
                    UPDATE DbVersion
                    SET currentVersion = 0
                    WHERE targetVersion = @currentVersion

                    IF @currentVersion < @givenVersion
                        BEGIN
                           WHILE @currentVersion < @givenVersion
                            BEGIN
                                DECLARE @procedureName NVARCHAR(50)
                                SET @currentVersion = @currentVersion + 1

                                SELECT @procedureName = procedureName
                                FROM DbVersion
                                WHERE targetVersion = @currentVersion
                                -- execute the procedure
                                EXEC @procedureName
                            END
                        END
                    ELSE
                        BEGIN
                           WHILE @currentVersion > @givenVersion
                            BEGIN
                                DECLARE @undoProcedureName NVARCHAR(50)

                                SELECT @undoProcedureName = undoProcedureName
                                FROM DbVersion
                                WHERE targetVersion = @currentVersion

                                -- execute the procedure
                                EXEC @undoProcedureName

                                SET @currentVersion = @currentVersion - 1
                            END
                        END

                    UPDATE DbVersion
                    SET currentVersion = 1
                    WHERE targetVersion = @givenVersion
                END
        END
END
GO

EXEC databaseVersion 0
GO


