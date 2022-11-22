USE CampeonPhotography
GO
-- Work on 3 tables of the form Ta(aid, a2, …), Tb(bid, b2, …), Tc(cid, aid, bid, …), where:
--
-- aid, bid, cid, a2, b2 are integers;
-- the primary keys are underlined;
-- a2 is UNIQUE in Ta;
-- aid and bid are foreign keys in Tc, referencing the primary keys in Ta and Tb, respectively.

drop table if exists Tc;
drop table if exists Tb;
drop table if exists Ta;

CREATE TABLE Ta(
    aid INT,
    a2 INT UNIQUE,
    x INT,
    CONSTRAINT pk_Ta PRIMARY KEY (aid)
)

CREATE TABLE Tb(
    bid INT,
    b2 INT,
    x INT,
    CONSTRAINT pk_Tb PRIMARY KEY (bid)
)

CREATE TABLE Tc(
    cid INT,
    aid INT,
    bid INT,
    CONSTRAINT pk_Tc PRIMARY KEY (cid),
    CONSTRAINT fk_TcTa FOREIGN KEY (aid) REFERENCES Ta(aid),
    CONSTRAINT fk_TcTb FOREIGN KEY (bid) REFERENCES Tb(bid)
)
GO

CREATE OR ALTER PROC insertIntoTable(@tableName VARCHAR(20), @nrOfRows INT) AS
    BEGIN
        DECLARE @value INT
        SET @value = 0

        WHILE @nrOfRows > 0
            BEGIN
                IF @tableName = 'Ta'
                    BEGIN
                        INSERT INTO Ta(aid, a2, x) VALUES (@nrOfRows, @value, @value % 10)
                    END

                IF @tableName = 'Tb'
                    BEGIN
                        INSERT INTO Tb(bid, b2, x) VALUES (@nrOfRows, @value, @value % 10)
                    END

                IF @tableName = 'Tc'
                    BEGIN
                        INSERT INTO Tc(cid, aid, bid) VALUES (@nrOfRows, (SELECT TOP 1 aid FROM Ta ORDER BY NEWID()), (SELECT TOP 1 bid FROM Tb ORDER BY NEWID()))
                    END

                SET @nrOfRows = @nrOfRows - 1
                SET @value = @value + 2
            END
    END
GO

EXEC insertIntoTable Ta, 10000
EXEC insertIntoTable Tb, 12000
EXEC insertIntoTable Tc, 4000

SELECT * FROM Ta;
SELECT * FROM Tb;
SELECT * FROM Tc;
GO

-- a. Write queries on Ta such that their execution plans contain the following operators:

-- On the tables Ta:
-- there hasn't been created a non-clustered index on the aid(primary key) column
-- a non-clustered index hasn't been specified on this column either
-- therefore a unique clustered index has been created on the primary key

-- clustered index scan;
SELECT * FROM Ta ORDER BY aid


-- clustered index seek;
SELECT * FROM Ta WHERE aid = 650


-- On the tables Ta:
-- there hasn't been created a clustered index on the a2 (unique) column
-- a clustered index hasn't been specified on this column either
-- therefore a non-clustered index has been created on the unique column a2

-- non-clustered index scan;
SELECT a2 FROM Ta


-- non-clustered index seek;
SELECT a2 FROM Ta WHERE a2 = 1000


-- On the tables Ta:
-- the column aid has a clustered index
-- the column a2 has a non clustered index
-- because we search based on the non-clustered index, da data doesn't contain the entire information about the record (only a2 and aid - the clustered index)
-- that is why once found a key lookup is performed to retrieve the desired information about that record (the x value)

-- key lookup.
SELECT x FROM Ta WHERE a2 = 400


-- b. Write a query on table Tb with a WHERE clause of the form WHERE b2 = value and analyze its execution plan.
-- Create a non-clustered index that can speed up the query. Examine the execution plan again.
SELECT * FROM Tb WHERE b2 = 450

-- include the bid and x as well so that a RID lookup is not needed
CREATE INDEX Tb_b2_non_clustered_index ON Tb(b2) INCLUDE (bid, x)
ALTER INDEX Tb_b2_non_clustered_index ON Tb DISABLE
ALTER INDEX Tb_b2_non_clustered_index ON Tb REBUILD

-- c. Create a view that joins at least 2 tables. Check whether existing indexes are helpful; if not, reassess existing indexes / examine the cardinality of the tables.
CREATE OR ALTER VIEW viewJoinTables AS
    SELECT Ta.a2, Tb.b2
    FROM Ta
    JOIN Tc on Ta.aid = Tc.aid
    JOIN Tb on Tb.bid = Tc.bid
    WHERE Ta.x = Tb.x
GO

SELECT * FROM viewJoinTables

CREATE INDEX Tc_aid_bid_non_clustered_index ON Tc(aid, bid)
ALTER INDEX Tc_aid_bid_non_clustered_index ON Tc DISABLE
ALTER INDEX Tc_aid_bid_non_clustered_index ON Tc REBUILD
