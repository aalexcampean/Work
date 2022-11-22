USE CampeonPhotography


DECLARE @cId INT
DECLARE @cModel VARCHAR(50)
SELECT TOP 1 @cId = id, @cModel = model
FROM Camera
ORDER BY NEWID()

PRINT @cId
PRINT @cModel

DECLARE @sampleTable TABLE(column1 INT, column2 VARCHAR(50))
INSERT INTO @sampleTable
    SELECT C.id, C.model
    FROM Camera C
    ORDER BY NEWID()
SELECT *
FROM @sampleTable

SELECT TOP 1 @cId = column1
FROM @sampleTable




GO