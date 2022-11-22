USE CampeonPhotography

-- INSERTS

INSERT INTO Photographer(name, surname, phoneNumber, email)
VALUES ('Alexandru', 'Campean', '+40737239658', 'al'),
       ('Abel', 'Pop', '+40723451289', 'ab'),
       ('Astrid', 'Merca', '+40754391223', 'as'),
       ('Jessica', 'Voiculescu', '+40755993821', 'je');
GO

INSERT INTO Camera(model, dateOfPurchase)
VALUES ('FUJIFILM X-T4', '2020-03-10'),
       ('SONY A7 III', '2020-06-05'),
       ('CANON EOS 5D MARK IV', '2020-10-22'),
       ('PANASONIC LUMIX DC S-5', '2020-12-02'),
       ('NIKON D500', '2021-04-30');
GO

INSERT INTO Client(name, surname, phoneNumber, email)
VALUES ('Alexandra', 'Gog', '+40745292396', 'gog_alexandra@yahoo.com'),
       ('Patric', 'Cota', '+40744203583', 'cota_patric@gmail.com'),
       ('Laura', 'Voicu', '+40724012029', 'voicu_laura@yahoo.com'),
       ('Serban', 'Mihu', '+40737156612', 'mihu_serban@yahoo.com'),
       ('Alex', 'Mintas', '+40740933344', 'mintas_alex@yahoo.com'),
       ('Catalin', 'Rebreanu', '+40741438883', 'rebreanu_cata@gmail.com'),
       ('Sarah', 'Nagy', '+40745363424', 'nagy_sarah@gmail.com'),
       ('Sofia', 'Crisan', '+40769679987', 'crisan_sofia@yahoo.com'),
       ('Serban', 'Gutiu', '+40722220048', 'gutiu_serban@gmail.com'),
       ('Cristina', 'Titu', '+40747923590', 'titu_cristina@gmail.com');
GO

INSERT INTO Location(name, address)
VALUES ('Fabrica de Sport', 'https://goo.gl/maps/e3ijG3FDhP5egUDFA'),
       ('Hala Bdv Muncii', 'https://goo.gl/maps/yQJY4wEWgNJ8hD3m6'),
       ('Platinia Mall', 'https://goo.gl/maps/4XzTRgp8RisSwX5R6'),
       ('Liberty Technology Park', 'https://goo.gl/maps/TKjZMdmET5y7itrt7'),
       ('The Office', 'https://goo.gl/maps/EysoNHQSvDDq1N5Z6'),
       ('Record Complex', 'https://goo.gl/maps/rRcuQinSiUpPrUyN8'),
       ('Samsara FoodHouse Indoor', 'https://goo.gl/maps/eg7SppTTQXZZ9rtM8');
GO

INSERT INTO Deadline(date)
VALUES ('2020-07-22'),
       ('2020-11-02'),
       ('2020-12-22'),
       ('2021-01-30'),
       ('2021-03-19'),
       ('2021-04-14');
GO

INSERT INTO Groups(name)
VALUES ('groupAlex03Jun'),
       ('groupAlex23Nov'),
       ('groupAbel03Dec'),
       ('groupAstrid10Jan'),
       ('groupAstrid08Mar'),
       ('groupJess01Apr');
GO

INSERT INTO GroupsMember(groupsId, clientId)
VALUES (1, 1),
       (1, 2),
       (1, 9),
       (2, 8),
       (3, 7),
       (3, 2),
       (4, 4),
       (5, 6),
       (5, 10),
       (6, 3);
GO

INSERT INTO PhotoShootBatch(cameraId,deadlineID)
VALUES (1, 1),
       (1, 2),
       (2, 3),
       (3, 4),
       (3, 5),
       (4, 6);
GO

INSERT INTO PhotoShoot(photographerId, photoShootBatchId, groupsId)
VALUES (1, 1, 1),
       (1, 2, 2),
       (2, 3, 3),
       (3, 4, 4),
       (3, 5, 5),
       (4, 6, 6);
GO

INSERT INTO PhotoShootLocation(photoShootId, locationId)
VALUES (1, 7),
       (2, 1),
       (3, 1),
       (4, 3),
       (5, 4),
       (6, 6);
GO

-- UPDATE

UPDATE Photographer
SET email = LOWER(name) + LOWER(LEFT(surname, 1)) + '.' + LOWER(surname) + '@campeon.ph'
GO

UPDATE Deadline
SET date = '2020-07-26'
WHERE id = 1
GO

UPDATE PhotoShootLocation
SET locationId = 6
WHERE photoShootId > 3
GO

UPDATE PhotoShoot
SET photographerId += 1
WHERE groupsId BETWEEN 2 AND 4
GO

-- DELETE

INSERT INTO Groups(name)
VALUES ('groupAlex03JunCopy'),
       ('groupAbel03DecCopy'),
       ('groupAstrid10JanCopy'),
       ('groupAstrid08MarCopy');
DELETE FROM Groups
WHERE name LIKE '%Copy'
GO

INSERT INTO PhotoShootBatch(cameraId,deadlineID)
VALUES (4, 1),
       (3, 2),
       (4, 3),
       (5, 4);
DELETE FROM PhotoShootBatch
WHERE id IN (11, 12, 13, 14)
GO

INSERT INTO Location(name, address)
VALUES ('Parcul Mare', 'https://goo.gl/maps/TsTdVVs49BLvBmxMA')
DELETE FROM Location
WHERE LEFT(name,1) = 'P' AND id > 7
GO

-- INSERT VIOLATING INTEGRITY CONSTRAINTS

INSERT INTO Location(name, address)
VALUES ('Skate Park Rozelor');
GO


-- A. 2 QUERIES WITH THE UNION OPERATION; USE UNION[ALL] AND OR


SELECT P.id, P.name
FROM Photographer P, PhotoShoot Ph, PhotoShootBatch Pb, Camera C
WHERE (P.id = Ph.photographerId AND Ph.photoShootBatchId = Pb.id
           AND Pb.cameraId = C.id AND C.model = 'FUJIFILM X-T4')
UNION
SELECT P.id, P.name
FROM Photographer P, PhotoShoot Ph, PhotoShootLocation Pl, Location L
WHERE (P.id = Ph.photographerId AND Pl.photoShootId = Ph.id
           AND PL.locationId = L.id AND L.name = 'Samsara FoodHouse Indoor')
GO

SELECT C.name AS 'ClientName', G.id AS 'GroupId', P.name AS 'PhotographerName'
FROM GroupsMember Gm
INNER JOIN Client C on C.id = Gm.clientId
INNER JOIN Groups G on G.id = Gm.groupsId
INNER JOIN PhotoShoot PS on G.id = PS.groupsId
INNER JOIN Photographer P on P.id = PS.photographerId
WHERE P.name = 'Abel' OR P.name = 'Astrid'
GO


-- B. 2 QUERIES WITH THE INTERSECTION OPERATION; USE INTERSECT AND IN


SELECT C.name AS 'ClientName'
FROM GroupsMember Gm
INNER JOIN Client C on C.id = Gm.clientId
INNER JOIN Groups G on G.id = Gm.groupsId
INNER JOIN PhotoShoot PS on G.id = PS.groupsId
INNER JOIN PhotoShootLocation PSL on PS.id = PSL.photoShootId
WHERE PS.id = 1
INTERSECT
SELECT C.name AS 'ClientName'
FROM GroupsMember Gm
INNER JOIN Client C on C.id = Gm.clientId
INNER JOIN Groups G on G.id = Gm.groupsId
INNER JOIN PhotoShoot PS on G.id = PS.groupsId
INNER JOIN PhotoShootLocation PSL on PS.id = PSL.photoShootId
WHERE PS.id = 4
GO

SELECT Pb.id AS 'PhotoShootBatchId'
FROM PhotoShootBatch Pb
WHERE Pb.id IN (
    SELECT Pb.id
    FROM Deadline D
    WHERE Pb.deadlineID = D.id AND YEAR(D.date) = 2020)
GO


-- C. 2 QUERIES WITH THE DIFFERENCE OPERATION; USE EXCEPT AND NOT IN


SELECT C.id AS "ClientId", C.name AS 'ClientName', C.email AS 'ClientEmail'
FROM Client C
INNER JOIN GroupsMember GM on C.id = GM.clientId AND GM.groupsId = 1
EXCEPT
SELECT C2.id AS "ClientId", C2.name AS 'ClientName', C2.email AS 'ClientEmail'
FROM Client C2
WHERE C2.email LIKE '%@yahoo.com'

SELECT C.id AS 'ClientId', C.name AS 'ClientName'
FROM Client C
WHERE C.id NOT IN (SELECT C2.id AS 'ClientId'
    FROM Client C2
    WHERE LEFT(C.name, 1) = 'A')
GO


-- D. 4 QUERIES WITH INNER JOIN, LEFT JOIN, RIGHT JOIN, AND FULL JOIN (ONE QUERY PER OPERATOR)
-- ONE QUERY WILL JOIN AT LEAST 3 TABLES, WHILE ANOTHER JOIN AT LEAST 2 MANY-TO-MANY RELATIONSHIPS


SELECT C.id, C.name
FROM GroupsMember
INNER JOIN Client C on C.id = GroupsMember.clientId
INNER JOIN Groups G on G.id = GroupsMember.groupsId
INNER JOIN PhotoShoot PS on G.id = PS.groupsId
INNER JOIN PhotoShootLocation PSL on PS.id = PSL.photoShootId
INNER JOIN Location L on L.id = PSL.locationId
WHERE L.id = 1
GO

SELECT DISTINCT P.id AS 'PhotographerId', P.name AS 'PhotographerName', PSB.cameraId AS 'CameraId'
FROM Photographer P
LEFT OUTER JOIN PhotoShoot S on P.id = S.photographerId
LEFT OUTER JOIN PhotoShootBatch PSB on S.photoShootBatchId = PSB.id AND PSB.cameraId > 2
GO

INSERT INTO Camera(model, dateOfPurchase)
VALUES ('CANON AE-1 PROGRAM', '2021-10-06');
SELECT PSB.id AS 'PhotoShootId', C.id AS 'CameraId', C.dateOfPurchase AS 'CameraDateOfPurchase'
FROM PhotoShootBatch PSB
RIGHT OUTER JOIN Camera C on C.id = PSB.cameraId
GO

INSERT INTO Photographer(name, surname, phoneNumber, email)
VALUES ('Kain', 'Rusu', '+40756334290', 'kainr.rusu@campeon.ph'),
       ('Robert', 'Chis', '+40745451229', 'robertc.chis@campeon.ph');
SELECT P.id AS 'PhotographerId', P.name AS 'PhotographerName', PS.id AS 'PhotoShootId'
FROM Photographer P
FULL OUTER JOIN PhotoShoot PS on P.id = PS.photographerId
GO


-- E. 2 QUERIES WITH THE IN OPERATOR AND A SUBQUERY IN THE WHERE CLAUSE
-- IN AT LEAST ONE CASE, THE SUBQUERY SHOULD INCLUDE A SUBQUERY IN ITS OWN WHERE CLAUSE


SELECT Pb.id AS 'PhotoShootBatchId', Pb.cameraId AS 'CameraId'
FROM PhotoShootBatch Pb
WHERE Pb.id IN (
    SELECT Pb.id
    FROM Camera C
    WHERE Pb.cameraId = C.id AND YEAR(C.dateOfPurchase) = 2020)
GO

SELECT D.id AS 'DateId'
FROM Deadline D
WHERE D.id IN (
    SELECT PSB.deadlineID
    FROM PhotoShootBatch PSB
    WHERE PSB.id IN (
        SELECT PS.photoShootBatchId
        FROM PhotoShoot PS
        WHERE PS.photoShootBatchId = PSB.id AND PS.photographerId = 1))
GO


-- F. 2 QUERIES WITH THE EXISTS OPERATOR AND A SUBQUERY IN THE WHERE CLAUSE


SELECT P.name AS 'PhotographerName'
FROM Photographer P
WHERE EXISTS(SELECT PS.groupsId
    FROM PhotoShoot PS
    WHERE PS.photographerId = P.id OR P.id > 4)
GO

ALTER TABLE PhotoShootBatch
ADD sent BIT DEFAULT 0
GO

UPDATE PhotoShootBatch
SET sent = 1
WHERE deadlineID < 5
GO

SELECT PS.id AS 'PhotoShootId'
FROM PhotoShoot PS
WHERE EXISTS(SELECT photoShootBatchId
    FROM PhotoShootBatch PSB
    WHERE PSB.id = PS.photoShootBatchId AND PSB.sent = 1)
GO


-- G. 2 QUERIES WITH A SUBQUERY IN THE FORM CLAUSE


INSERT INTO GroupsMember(groupsId, clientId)
VALUES (6, 5)
GO

SELECT GM.groupsId, CA.id, CA.name, CA.surname
FROM GroupsMember GM INNER JOIN (SELECT C.id, C.name, C.surname
    FROM Client C
    WHERE LEFT(C.name, 1) = 'A') CA
ON GM.clientId = CA.id
GO

SELECT SP.id, SP.name, SP.surname
FROM (SELECT P.id, P.name, P.surname
    FROM Photographer P
    WHERE P.phoneNumber LIKE '___75%') SP
WHERE LEFT(SP.name, 1) = 'A' OR LEFT(SP.name, 1) = 'K'
GO


-- H. 4 QUERIES WITH THE GROUP BY CLAUSE, 3 OF WHICH ALSO CONTAIN THE HAVING CLAUSE;
-- 2 OF THE LATTER WILL ALSO HAVE A SUBQUERY IN THE HAVING CLAUSE;
-- USE THE AGGREGATION OPERATORS: COUNT, SUM, AVG, MIN, MAX;


ALTER TABLE Photographer
ADD dateOfBirth DATE
GO

ALTER TABLE Client
ADD dateOfBirth DATE
GO

SELECT TOP 1 PS.photographerId AS 'PhotographerId', COUNT(PS.id) AS 'NumberOfPhotoShoots'
FROM PhotoShoot PS
GROUP BY PS.photographerId
HAVING COUNT(PS.id) > 1
GO

SELECT P.id, P.name, P.dateOfBirth, (SELECT YEAR(GETDATE()) - YEAR(P.dateOfBirth)) AS 'Age'
FROM Photographer P
GROUP BY P.id, P.name, P.dateOfBirth
HAVING P.dateOfBirth = (SELECT MIN(P2.dateOfBirth)
    FROM Photographer P2)
GO

SELECT TOP 1 C2.id, C2.model, MAX(C2.NumberOfUses) AS 'NumberOfUses'
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
GO

SELECT PSB2.id, PSB2.Deadline
FROM (SELECT PSB.id, D.date AS 'Deadline'
    FROM PhotoShootBatch PSB
    INNER JOIN Deadline D on D.id = PSB.deadlineID
    GROUP BY PSB.id, PSB.sent, D.date
    HAVING PSB.sent = 0) PSB2
GROUP BY PSB2.id, PSB2.Deadline
HAVING PSB2.Deadline = (SELECT MIN(PSB4.Deadline)
        FROM (SELECT PSB3.id, D2.date AS 'Deadline'
            FROM PhotoShootBatch PSB3
            INNER JOIN Deadline D2 on D2.id = PSB3.deadlineID
            GROUP BY PSB3.id, PSB3.sent, D2.date
            HAVING PSB3.sent = 0) PSB4)
GO


-- i. 4 QUERIES USING ANY AND ALL TO INTRODUCE A SUBQUERY IN THE WHERE CLAUSE (2 QUERIES PER OPERATOR);
-- REWRITE 2 OF THEM WITH AGGREGATION OPERATORS, AND THE OTHER 2 WITH IN / [NOT] IN;


SELECT C.id AS 'ClientId', C.name + ' ' + C.surname AS 'ClientNameSurname'
FROM Client C
WHERE C.dateOfBirth <= ALL(SELECT C2.dateOfBirth
    FROM Client C2)
GO

SELECT C.id AS 'CameraId', C.model AS 'CameraModel'
FROM Camera C
WHERE C.dateOfPurchase >= ALL(SELECT C2.dateOfPurchase
    FROM Camera C2)
GO

SELECT PS.id AS 'PhotoShootId'
FROM PhotoShoot PS
WHERE photoShootBatchId = ANY(SELECT PSB.id
    FROM PhotoShootBatch PSB
    WHERE PSB.sent = 1)
GO

SELECT PSL.photoShootId AS 'PhotoShootId', PS.photographerId AS 'PhotographerId'
FROM PhotoShootLocation PSL
INNER JOIN PhotoShoot PS on PS.id = PSL.photoShootId
WHERE PSL.id = ANY(SELECT PSL2.id
    FROM PhotoShootLocation PSL2
    INNER JOIN Location L on L.id = PSL2.locationId
    WHERE L.address = 'https://goo.gl/maps/rRcuQinSiUpPrUyN8')
GO

-- REWRITE

SELECT DISTINCT C.id AS 'ClientId', C.name + ' ' + C.surname AS 'ClientNameSurname', (SELECT YEAR(GETDATE()) - YEAR(C.dateOfBirth)) AS 'Age'
FROM Client C
WHERE C.dateOfBirth = (SELECT MIN(C2.dateOfBirth)
    FROM Client C2)
GO

SELECT DISTINCT C.id AS 'CameraId', C.model AS 'CameraModel', (SELECT MONTH(GETDATE()) - MONTH(C.dateOfPurchase)) AS 'Months had'
FROM Camera C
WHERE C.dateOfPurchase = (SELECT MAX(C2.dateOfPurchase)
    FROM Camera C2)
GO

SELECT DISTINCT PS.id AS 'PhotoShootId'
FROM PhotoShoot PS
WHERE photoShootBatchId IN (SELECT PSB.id
    FROM PhotoShootBatch PSB
    WHERE PSB.sent = 1)
GO

SELECT PSL.photoShootId AS 'PhotoShootId', PS.photographerId AS 'PhotographerId'
FROM PhotoShootLocation PSL
INNER JOIN PhotoShoot PS on PS.id = PSL.photoShootId
WHERE PSL.id NOT IN(SELECT PSL2.id
    FROM PhotoShootLocation PSL2
    INNER JOIN Location L on L.id = PSL2.locationId
    WHERE L.address != 'https://goo.gl/maps/rRcuQinSiUpPrUyN8')
GO