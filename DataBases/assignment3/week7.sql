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

CREATE TABLE Lens(
  id INT NOT NULL PRIMARY KEY IDENTITY(1,1),
  model VARCHAR(50) NOT NULL,
  dateOfPurchase DATE
);

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




CREATE TABLE DbVersion(
    do VARCHAR(50) NOT NULL,
    redo VARCHAR(50) NOT NULL,
    targetVersion INT NOT NULL
);

